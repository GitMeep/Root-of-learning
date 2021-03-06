#pragma once

#include "../resource.h"

namespace ROK::API::Resources {

class Category : public Resource {
public:
    inline std::string getName() {return "Category";}

protected:
    void get(HTTPRequest& request, PathVariables& pathVars, HTTPResponse& response);
    void post(HTTPRequest& request, PathVariables& pathVars, HTTPResponse& response);
};

};
