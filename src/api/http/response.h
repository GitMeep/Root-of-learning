#pragma once

#include "message.h"
#include "statusCode.h"

class HTTPResponse : public HTTPMessage {
public:
    HTTPResponse();
    HTTPResponse(const std::string& body, const HTTPHeaders& headers, const HTTPStatusCode& status, const std::string& version = "1.1");

    std::string toRawMessage();

    void setStatus(const HTTPStatusCode& code);

private:
    HTTPStatusCode _statusCode;

};