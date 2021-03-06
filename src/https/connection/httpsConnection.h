#pragma once

#include <asio.hpp>
#include <asio/ssl.hpp>
#include <memory>

#include "streamParser.h"
#include "../httpsServer.h"

class HTTPSConnectionManager;

using namespace asio::ip;

class HTTPSConnection {
public:
    HTTPSConnection(asio::io_context& io_context, asio::ssl::context& sslContext, HTTPSConnectionManager& connManager, HTTPSServer::RequestHandlerFn& requestHandler);

    asio::ssl::stream<tcp::socket>::lowest_layer_type& socket();

    void start();
    void stop();

private:
    asio::ssl::stream<tcp::socket> _sslSocket;
    asio::io_context& _ioContext;
    HTTPSConnectionManager& _connManager;

    HTTPSServer::RequestHandlerFn& _requestHandler;

    HTTPStreamParser _reader;
    char _data[1024];

    bool _keepAlive;

    void readSome();

    void handleWrite(const asio::error_code& error, size_t bytes);
    void handleRead(const asio::error_code& error, size_t bytes);
    void handleHandshake(const asio::error_code& error);

    void onCompleteMessage(HTTPRequest& request);
};