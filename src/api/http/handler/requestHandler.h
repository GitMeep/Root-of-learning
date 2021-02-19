#pragma once

#include <asio.hpp>
#include <api/http/message.h>
#include <vector>

#include "../endpoint/endpoint.h"

class HTTPRequestHandler {
public:
    HTTPRequestHandler(asio::io_context& ioContext);

    std::string handleRequest(HTTPRequest request);

    void registerEndpoint(HTTPEndpoint& endpoint);

private:
    asio::io_context& _ioContext;

    std::vector<HTTPEndpoint> _endpoints;

};