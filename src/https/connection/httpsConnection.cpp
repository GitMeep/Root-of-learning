#include "./httpsConnection.h"

#include <iostream>

#include "httpsConnectionManager.h"

HTTPSConnection::HTTPSConnection(asio::io_context& io_context, asio::ssl::context& sslContext, HTTPSConnectionManager& connManager, HTTPSServer::RequestHandlerFn& requestHandler)
 : _sslSocket(io_context, sslContext)
 , _connManager(connManager)
 , _ioContext(io_context)
 , _requestHandler(requestHandler)
 , _reader(std::bind(&HTTPSConnection::onCompleteMessage, this, std::placeholders::_1)) {
    _keepAlive = true;
}

void HTTPSConnection::start() {
    _sslSocket.async_handshake(asio::ssl::stream_base::server,
        std::bind(&HTTPSConnection::handleHandshake, this, std::placeholders::_1));
}

void HTTPSConnection::stop() {
    _sslSocket.async_shutdown([this](...) {
        socket().cancel();
        socket().close();
        delete this;
    });
}

void HTTPSConnection::handleHandshake(const asio::error_code& error) {
    if(!error) {
        readSome();
    } else {
        _connManager.stop(this);
    }
}

void HTTPSConnection::readSome() {
    _sslSocket.async_read_some(asio::buffer(_data, 1024), std::bind(&HTTPSConnection::handleRead, this, std::placeholders::_1, std::placeholders::_2));
}

void HTTPSConnection::handleRead(const asio::error_code& error, size_t bytes) {
    if(!error) {
        std::string buf;
        buf.resize(bytes);
        memcpy((void*)buf.c_str(), _data, bytes);

        _reader.readNext(buf);
        readSome();
    } else {
        _connManager.stop(this);
    }
}

void HTTPSConnection::onCompleteMessage(HTTPRequest& request) {
    std::string connection = request.getHeader("Connection");
    if(connection == "close") {
        _keepAlive = false;
    } else {
        _keepAlive = true;
    }

    std::string replyData = _requestHandler(request).toRawMessage();
    _sslSocket.async_write_some(asio::buffer(replyData), std::bind(&HTTPSConnection::handleWrite, this, std::placeholders::_1, std::placeholders::_2));
}

void HTTPSConnection::handleWrite(const asio::error_code& error, size_t bytes) {
    if(!_keepAlive || error)
        _connManager.stop(this);
}

asio::ssl::stream<tcp::socket>::lowest_layer_type& HTTPSConnection::socket() {
    return _sslSocket.lowest_layer();
}
