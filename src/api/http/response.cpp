#include "response.h"

HTTPResponse::HTTPResponse() {
    HTTPMessage();
}

HTTPResponse::HTTPResponse(const std::string& body, const HTTPHeaders& headers, const HTTPStatusCode& status, const std::string& version)
 : HTTPMessage(body, headers, version) {
    _statusCode = status;
}

void HTTPResponse::setStatus(const HTTPStatusCode& code) {
    _statusCode = code;
}

std::string HTTPResponse::toRawMessage() {
    std::string startLine = std::string("HTTP/" + _httpVersion + " ") + _statusCode.getString();
    return HTTPMessage::toRawMessage(startLine);
}
