#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <spdlog/spdlog.h>

#include <api/https/request.h>
#include <api/https/endpoint/endpoint.h>

namespace ROK::API::Endpoint {

class Endpoint {
public:
    struct EndpointInfo {
        std::string name;
        EndpointPath path;
        std::unordered_map<HTTPRequest::Method, HTTPEndpoint::EndpointHandler> handlers;
    };

    Endpoint();

    virtual EndpointInfo getInfo() = 0;

protected:
    std::shared_ptr<spdlog::logger> _log;

};

};