#include "requestHandler.h"

#include "../response.h"
#include "../request.h"

HTTPRequestHandler::HTTPRequestHandler(asio::io_context& ioContext)
 : _ioContext(ioContext) {

}

std::string HTTPRequestHandler::handleRequest(HTTPRequest request) {
    HTTPResponse response;
    bool found = false;
    for(auto endpoint : _endpoints) {
        if(endpoint.matchAndCall(request, response)) {
            found = true;
            break;
        }
    }

    if(!found) {
        response.setStatus(HTTPStatusCode::NOT_FOUND);
        response.setBody("{\"Code\": 404, \"Message\": \"Endpoint not found.\"}");
    }

    return response.toRawMessage();
}

void HTTPRequestHandler::registerEndpoint(HTTPEndpoint& endpoint) {
    for(auto e : _endpoints) {
        if(endpoint.getPath() == e.getPath()) {
            return;
        }
    }

    _endpoints.emplace_back(endpoint);
}
