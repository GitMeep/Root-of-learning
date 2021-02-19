#pragma once

#include <asio.hpp>
#include <memory>
#include <spdlog/spdlog.h>

#include <api/server.h>

class Trunk {
public:
    Trunk();

    static Trunk& instance();
    void run();

    asio::io_context& getContext();

private:
    std::shared_ptr<ApiServer> mApiServer;
    asio::io_context _ioContext;
    std::shared_ptr<spdlog::logger> _log;
};