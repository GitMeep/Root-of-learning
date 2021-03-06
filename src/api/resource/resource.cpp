#include "resource.h"

void respondNoMethod(HTTPResponse& response, const std::string& method) {
    response.setStatus(HTTPStatusCode::METHOD_NOT_ALLOWED);
    response.setBody("{\"code\": \"405 Method Not Allowed\", \"message\": \"This method doesn't exist on this resource\"}");
}

namespace ROK::API {

Resource::Resource() {
    _log = spdlog::get("console");
}

void Resource::call(HTTPRequest& request, PathVariables& pathVars, HTTPResponse& response) {
    switch(request.getMethod()) {
        case HTTPRequest::GET:
            this->get(request, pathVars, response);
            return;
        
        case HTTPRequest::POST:
            this->post(request, pathVars, response);
            return;

        case HTTPRequest::PUT:
            this->put(request, pathVars, response);
            return;

        case HTTPRequest::DELETE:
            this->del(request, pathVars, response);
            return;
    };
}

void Resource::put(HTTPRequest& request, PathVariables& pathVars, HTTPResponse& response) {
    respondNoMethod(response, "PUT");
}

void Resource::del(HTTPRequest& request, PathVariables& pathVars, HTTPResponse& response) {
    respondNoMethod(response, "DELETE");
}

};
