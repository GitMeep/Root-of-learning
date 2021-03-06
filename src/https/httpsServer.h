#pragma once

#include <asio.hpp>
#include <asio/ssl.hpp>
#include <set>

#include "connection/httpsConnectionManager.h"
#include "response.h"
#include "request.h"

class HTTPSServer {
public:
    typedef std::function<HTTPResponse(HTTPRequest)> RequestHandlerFn;

    HTTPSServer(asio::io_context& io_context, unsigned short port);

    void start();
    void stop();

    void setHandler(RequestHandlerFn fn);

private:
    asio::io_context& _ioContext;
    asio::ip::tcp::acceptor _acceptor;
    asio::ssl::context _sslContext;

    HTTPSConnectionManager _connManager;

    RequestHandlerFn _requestHandler;

    std::string getSSLPassword() const;

    void acceptNew();
    void handleAccept(HTTPSConnection* conn, const asio::error_code& err);

};