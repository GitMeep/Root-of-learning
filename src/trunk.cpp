#include "trunk.h"

#include <spdlog/sinks/stdout_color_sinks.h>

Trunk::Trunk() {
    _log = spdlog::stdout_color_mt("console");
    _log->set_pattern("%^[%D] [%H:%M:%S] [th#%t] [%L]%$: %v");

    mApiServer = std::make_shared<ApiServer>(_ioContext, 1337);
}

Trunk& Trunk::instance() {
    static Trunk instance;
    return instance;
}

asio::io_context& Trunk::getContext() {
    return _ioContext;
}

void Trunk::run() {
    _log->info("Starting Roots of Knowledge V" + std::string(RON_VERSION));

    mApiServer->start();
    _ioContext.run();
}