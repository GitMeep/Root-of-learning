#include "category.h"

namespace ROK::API::Endpoint {

HTTPResponse Category::getCategory(HTTPRequest request, EndpointPath::PathVariables pathVars) {
    HTTPResponse response;
    response.setBody("This is the category endpoint, the id is " + pathVars["id"]);


    return response;
}

Endpoint::EndpointInfo Category::getInfo() {
    EndpointPath path;
    path.addPart("category").addPart("id", true);
    std::unordered_map<HTTPRequest::Method, HTTPEndpoint::EndpointHandler> handlers;

    return {
        "Category",
        path,
        {
            {HTTPRequest::GET, std::bind(&Category::getCategory, this, std::placeholders::_1, std::placeholders::_2)}
        }
    };
}

};
