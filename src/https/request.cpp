#include "request.h"

#include <unordered_map>

HTTPRequest::HTTPRequest() {
    HTTPMessage();

    _method = GET;
}

HTTPRequest::Method HTTPRequest::getMethod() {
    return _method;
}

std::string HTTPRequest::getPath() {
    return _path;
}

void HTTPRequest::setMethod(const Method& method) {
    _method = method;
}

void HTTPRequest::setMethod(const std::string& str) {
    _method = methodFromString(str);
}

void HTTPRequest::setPath(const std::string& path) {
    _path = path;
}

HTTPRequest::Method HTTPRequest::methodFromString(const std::string& methodString) {
    static const std::unordered_map<std::string, HTTPRequest::Method> methodsMap = {
        {"GET", GET},
        {"HEAD", HEAD},
        {"POST", POST},
        {"PUT", PUT},
        {"DELTE", DELETE},
        {"CONNECT", CONNECT},
        {"OPTIONS", OPTIONS},
        {"TRACE", TRACE},
        {"PATCH", PATCH}
    };

    if(methodsMap.count(methodString) == 0) return UNKNOWN;

    return methodsMap.find(methodString)->second;
}
