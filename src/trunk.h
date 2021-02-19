#pragma once

#include <asio.hpp>
#include <memory>
#include <spdlog/spdlog.h>

#include <api/server.h>

namespace ROK {

class Trunk {
public:
    Trunk();

    static Trunk& instance();
    void run();

    asio::io_context& getContext();

private:
    std::shared_ptr<API::Server> _apiServer;
    asio::io_context _ioContext;
    std::shared_ptr<spdlog::logger> _log;
};

};
