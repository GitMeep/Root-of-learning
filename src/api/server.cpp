#include "server.h"

namespace ROK::API {

Server::Server(asio::io_context& io_context, unsigned short port) 
: _httpsServer(io_context, port)
, _port(port) {
    _log = spdlog::get("console");

    _httpsServer.setHandler(std::bind(&RequestHandler::handleRequest, &_requestHandler, std::placeholders::_1));
}

Server::~Server() {
    for(auto e : _resources)
        delete e;
}

void Server::registerResource(Resource* resource, ROK::API::ResourcePath &path) {
    _resources.emplace_back(resource);

    _requestHandler.registerResource(resource, path);
}

void Server::start() {
    _log->info("Starting API server on port {}", _port);
    _httpsServer.start();
}

void Server::stop() {
    _httpsServer.stop();
}

};
