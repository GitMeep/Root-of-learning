#include "server.h"

#include "http/endpoint/endpoint.h"

ApiServer::ApiServer(asio::io_context& io_context, unsigned short port) 
: _httpsServer(io_context, port) {
    _port = port;
    _log = spdlog::get("console");

    EndpointPath testPath;
    testPath.addPart("", false);

    HTTPEndpoint endpoint("Test", testPath);
    endpoint.addMethodHandler(HTTPRequest::GET, [](HTTPRequest request, EndpointPath::PathVariables vars) -> HTTPResponse {
        HTTPResponse response("This is a test", {}, HTTPStatusCode::OK);
        return response;
    });
    _httpsServer.registerEndpoint(endpoint);

}

void ApiServer::start() {
    _log->info("Starting API server on port {}", _port);
    _httpsServer.start();
}

void ApiServer::stop() {
    _httpsServer.stop();
}
