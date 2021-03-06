#pragma once

#include <asio.hpp>
#include <vector>

#include <api/resource/resource.h>
#include <api/resource/resourcePath.h>

#include <https/request.h>

namespace ROK::API {

class RequestHandler {
public:
    HTTPResponse handleRequest(HTTPRequest request);

    void registerResource(Resource* resource, ResourcePath& path);

private:
    std::vector<std::pair<ResourcePath, Resource*>> _resources;

};

};