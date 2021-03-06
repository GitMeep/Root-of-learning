#include "category.h"

namespace ROK::API::Resources {

void Category::get(HTTPRequest& request, PathVariables& pathVars, HTTPResponse& response) {
    response.setBody("This is the GET method on the category resource, the id is " + pathVars["id"]);
}

void Category::post(HTTPRequest& request, PathVariables& pathVars, HTTPResponse& response) {
    response.setBody("This is the POST method on the category resource, the id is " + pathVars["id"]);
}

};
