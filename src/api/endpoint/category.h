#pragma once

#include "endpoint.h"

namespace ROK::API::Endpoint {

class Category : public Endpoint {
public:
    HTTPResponse getCategory(HTTPRequest request, EndpointPath::PathVariables pathVars);

    EndpointInfo getInfo();
};

};
