#include "message.h"

#include <sstream>

HTTPMessage::HTTPMessage(const std::string& body, const HTTPHeaders& headers, const std::string& version) {
    _headers = headers;
    _body = body;
    _httpVersion = version;
}

HTTPMessage::HTTPMessage() {
    _headers.clear();
    _body = "";
    _httpVersion = "1.1";
}

void HTTPMessage::setHeader(const std::string& key, const std::string& value) {
    _headers[key] = value;
}

void HTTPMessage::setVersion(const std::string& version) {
    _httpVersion = version;
}

void HTTPMessage::removeHeader(const std::string& key) {
    _headers.erase(key);
}

bool HTTPMessage::hasHeader(const std::string& key) {
    return (_headers.count(key) == 1);
}

std::string HTTPMessage::getHeader(const std::string& key) {
    if(_headers.count(key) == 1) {
        return _headers[key];
    }
    return "";
}

void HTTPMessage::setBody(const std::string& body) {
    _body = body;
}

std::string HTTPMessage::getBody() {
    return _body;
}

std::string HTTPMessage::getVersion() {
    return _httpVersion;
}

std::string HTTPMessage::toRawMessage(std::string& startLine) {
    std::string rawMessage = (startLine += "\n");
    if(!hasHeader("Content-Length")) {
        rawMessage += ("Content-Length: " + std::to_string(_body.length()) + "\n");
    }

    for(auto header : _headers) {
        rawMessage += header.first + ": " + header.second + "\n";
    }
    rawMessage += "\n";
    rawMessage += _body;

    return rawMessage;
}
