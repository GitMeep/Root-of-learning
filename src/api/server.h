#pragma once

#include <asio.hpp>
#include <asio/ssl.hpp>
#include <spdlog/spdlog.h>
#include <memory>
#include <vector>

#include <https/httpsServer.h>
#include <api/handler/requestHandler.h>
#include "resource/resource.h"

namespace ROK::API {

class Server {
public:
    Server(asio::io_context& io_context, unsigned short port);
    ~Server();

    void registerResource(Resource* resource, ROK::API::ResourcePath &path);

    void start();
    void stop();

private:
    HTTPSServer _httpsServer;
    std::shared_ptr<spdlog::logger> _log;
    unsigned short _port;

    std::vector<Resource*> _resources;
    RequestHandler _requestHandler;
};

};
