#include "requestHandler.h"

#include <https/request.h>
#include <https/response.h>

namespace ROK::API {

HTTPResponse RequestHandler::handleRequest(HTTPRequest request) {
    HTTPResponse response;
    bool found = false;
    for(auto resource : _resources) {
        std::string path = request.getPath();
        auto vars = resource.first.matchAndGetVars(path);
        if(vars.count("no match") == 0) {
            resource.second->call(request, vars, response);
            found = true;
            break;
        }
    }

    if(!found) {
        response.setStatus(HTTPStatusCode::NOT_FOUND);
        response.setBody("{\"Code\": 404, \"Message\": \"Endpoint not found.\"}");
    }

    return response;
}

void RequestHandler::registerResource(Resource* resource, ResourcePath& path) {
    for(auto r : _resources) {
        if(path == r.first) {
            return;
        }
    }

    _resources.emplace_back(path, resource);
}

};