#include "httpsServer.h"

#include "connection/httpsConnection.h"

using namespace asio::ip;

HTTPSServer::HTTPSServer(asio::io_context& io_context, unsigned short port)
: _ioContext(io_context)
, _acceptor(io_context, tcp::endpoint(tcp::v4(), port))
, _sslContext(asio::ssl::context::tlsv12)
, _requestHandler(io_context) {
    ///////////////////////////////////////////
    _sslContext.set_options(
        asio::ssl::context::default_workarounds
        | asio::ssl::context::no_sslv2
        | asio::ssl::context::no_sslv3
        );
    _sslContext.set_verify_mode(asio::ssl::context::verify_fail_if_no_peer_cert);
    _sslContext.set_password_callback(std::bind(&HTTPSServer::getSSLPassword, this));
    _sslContext.use_certificate_file("cert.pem", asio::ssl::context::pem);
    _sslContext.use_private_key_file("key.pem", asio::ssl::context::pem);
}

void HTTPSServer::start() {
    acceptNew();
}

void HTTPSServer::stop() {
    _acceptor.cancel();
}

void HTTPSServer::registerEndpoint(HTTPEndpoint& endpoint) {
    _requestHandler.registerEndpoint(endpoint);
}

std::string HTTPSServer::getSSLPassword() const {
    return "ThisIsJustATest"; // get from config file or something
}

void HTTPSServer::acceptNew() {
    HTTPSConnection* newConnection = new HTTPSConnection(_ioContext, _sslContext, _connManager, _requestHandler);

    _acceptor.async_accept(newConnection->socket(), std::bind(&HTTPSServer::handleAccept, this, newConnection, std::placeholders::_1));
}

void HTTPSServer::handleAccept(HTTPSConnection* conn, const asio::error_code& err) {
    if(!err) {
        _connManager.start(conn);
    }

    acceptNew();
}