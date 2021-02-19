#pragma once

#include <asio.hpp>
#include <asio/ssl.hpp>
#include <set>

#include "connection/httpsConnectionManager.h"
#include "handler/requestHandler.h"
#include "endpoint/endpoint.h"

class HTTPSServer {
public:
    HTTPSServer(asio::io_context& io_context, unsigned short port);

    void start();
    void stop();

    void registerEndpoint(HTTPEndpoint& endpoint);

private:
    asio::io_context& _ioContext;
    asio::ip::tcp::acceptor _acceptor;
    asio::ssl::context _sslContext;

    HTTPSConnectionManager _connManager;

    HTTPRequestHandler _requestHandler;

    std::string getSSLPassword() const;

    void acceptNew();
    void handleAccept(HTTPSConnection* conn, const asio::error_code& err);

};