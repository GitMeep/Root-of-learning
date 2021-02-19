#include "trunk.h"

#include <spdlog/sinks/stdout_color_sinks.h>

#include <api/endpoint/endpoints.h>
namespace ROK {

Trunk::Trunk() {
    _log = spdlog::stdout_color_mt("console");
    _log->set_pattern("%^[%D] [%H:%M:%S] [th#%t] [%L]%$: %v");

    _apiServer = std::make_shared<API::Server>(_ioContext, 1337);
    _apiServer->registerEndpoint(new ROK::API::Endpoint::Category);

}

Trunk& Trunk::instance() {
    static Trunk instance;
    return instance;
}

asio::io_context& Trunk::getContext() {
    return _ioContext;
}

void Trunk::run() {
    _log->info("Starting Roots of Knowledge V" + std::string(ROK_VERSION));

    _apiServer->start();
    _ioContext.run();
}

};
