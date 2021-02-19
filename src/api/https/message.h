#pragma once

#include <unordered_map>
#include <string>

class HTTPMessage {
public:
    typedef std::unordered_map<std::string, std::string> HTTPHeaders;

    HTTPMessage(const std::string& body, const HTTPHeaders& headers, const std::string& version);
    HTTPMessage();

    void setVersion(const std::string& version);
    void setHeader(const std::string& key, const std::string& value);
    void removeHeader(const std::string& key);
    void setBody(const std::string& body);

    std::string getVersion();
    bool hasHeader(const std::string& key);
    std::string getHeader(const std::string& key);
    std::string getBody();

    std::string toRawMessage(std::string& starLine);

protected:
    std::string _httpVersion;
    HTTPHeaders _headers;
    std::string _body;

};