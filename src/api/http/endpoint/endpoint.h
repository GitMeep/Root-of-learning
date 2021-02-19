#pragma once

#include <string>
#include <functional>
#include <unordered_map>

#include "endpointPath.h"
#include "../response.h"
#include "../request.h"

class HTTPEndpoint {
public:
    typedef std::function<HTTPResponse(HTTPRequest, EndpointPath::PathVariables)> EndpointHandler;
    HTTPEndpoint(const std::string& name, const EndpointPath& path);

    void addMethodHandler(HTTPRequest::Method method, EndpointHandler handler);
    HTTPResponse call(HTTPRequest request, EndpointPath::PathVariables pathVars);
    bool matchAndCall(HTTPRequest& request, HTTPResponse& response);

    EndpointPath getPath();

private:
    std::unordered_map<HTTPRequest::Method, EndpointHandler> _handlers;

    std::string _name;
    EndpointPath _path;
};