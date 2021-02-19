#pragma once

#include <asio.hpp>
#include <asio/ssl.hpp>
#include <spdlog/spdlog.h>
#include <memory>
#include <vector>

#include "https/httpsServer.h"
#include "endpoint/endpoint.h"

namespace ROK::API {

class Server {
public:
    Server(asio::io_context& io_context, unsigned short port);
    ~Server();

    void registerEndpoint(Endpoint::Endpoint* endpoint);

    void start();
    void stop();

private:
    HTTPSServer _httpsServer;
    std::shared_ptr<spdlog::logger> _log;
    unsigned short _port;

    std::vector<Endpoint::Endpoint*> _endpoints;
};

};
