#include "server.h"

#include "https/endpoint/endpoint.h"

namespace ROK::API {

Server::Server(asio::io_context& io_context, unsigned short port) 
: _httpsServer(io_context, port)
, _port(port) {
    _log = spdlog::get("console");
}

Server::~Server() {
    for(auto e : _endpoints)
        delete e;
}

void Server::registerEndpoint(Endpoint::Endpoint* endpoint) {
    _endpoints.emplace_back(endpoint);

    auto info = endpoint->getInfo();
    HTTPEndpoint ep(info.name, info.path);
    for(auto handler : info.handlers) {
        ep.addMethodHandler(handler.first, handler.second);
    }
    _httpsServer.registerEndpoint(ep);
}

void Server::start() {
    _log->info("Starting API server on port {}", _port);
    _httpsServer.start();
}

void Server::stop() {
    _httpsServer.stop();
}

};
