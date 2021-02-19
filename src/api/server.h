#pragma once

#include <asio.hpp>
#include <asio/ssl.hpp>
#include <spdlog/spdlog.h>
#include <memory>


#include "http/httpsServer.h"

class ApiServer {
public:
    ApiServer(asio::io_context& io_context, unsigned short port);

    void start();
    void stop();

private:
    HTTPSServer _httpsServer;
    std::shared_ptr<spdlog::logger> _log;
    unsigned short _port;
};
