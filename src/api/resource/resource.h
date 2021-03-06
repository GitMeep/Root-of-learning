#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <spdlog/spdlog.h>

#include <https/request.h>
#include <https/response.h>
#include "resourcePath.h"

namespace ROK::API {

class Resource {
public:
    Resource();

    virtual inline std::string getName() = 0;

    void call(HTTPRequest& request, PathVariables& pathVars, HTTPResponse& response);

protected:
    virtual void get(HTTPRequest& request, PathVariables& pathVars, HTTPResponse& response) = 0;
    virtual void post(HTTPRequest& request, PathVariables& pathVars, HTTPResponse& response) = 0;
    virtual void put(HTTPRequest& request, PathVariables& pathVars, HTTPResponse& response);
    virtual void del(HTTPRequest& request, PathVariables& pathVars, HTTPResponse& response);

    std::shared_ptr<spdlog::logger> _log;

};

};
