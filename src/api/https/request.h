#pragma once

#include <string>

#include "message.h"

class HTTPRequest : public HTTPMessage {
public:
    enum Method {
        GET,
        HEAD,
        POST,
        PUT,
        DELETE,
        CONNECT,
        OPTIONS,
        TRACE,
        PATCH,
        UNKNOWN
    };

    HTTPRequest();
    HTTPRequest(const HTTPMessage& message);

    Method getMethod();
    std::string getPath();

    void setMethod(const Method& method);
    void setMethod(const std::string& str);
    void setPath(const std::string& path);

    static Method methodFromString(const std::string& methodString);

private:
    Method _method;
    std::string _path;

};