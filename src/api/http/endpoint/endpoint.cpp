#include "endpoint.h"

#include "../statusCode.h"

HTTPEndpoint::HTTPEndpoint(const std::string& name, const EndpointPath& path) {
    _path = path;
    _name = name;
}

bool HTTPEndpoint::matchAndCall(HTTPRequest& request, HTTPResponse& response) {
    std::string path = request.getPath();
    EndpointPath::PathVariables pathVars = _path.matchAndGetVars(path);

    if(pathVars.count("no match") == 1) {
        return false;
    }

    response = call(request, pathVars);
    return true;
}

HTTPResponse HTTPEndpoint::call(HTTPRequest request, EndpointPath::PathVariables pathVars) {
    HTTPResponse response;
    if(_handlers.count(request.getMethod()) == 0) {
        HTTPStatusCode statusCode(HTTPStatusCode::METHOD_NOT_ALLOWED);
        return HTTPResponse("{\"Status Code\": \"" + statusCode.getString() + "\", \"Message\": \"Endpoint " + _name + " does not support this method\"}", {}, statusCode);
    }

    response = _handlers[request.getMethod()](request, pathVars);

    return response;
}

void HTTPEndpoint::addMethodHandler(HTTPRequest::Method method, EndpointHandler handler) {
    _handlers[method] = handler;
}

EndpointPath HTTPEndpoint::getPath() {
    return _path;
}
