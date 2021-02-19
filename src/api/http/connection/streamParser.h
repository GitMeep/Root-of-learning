#pragma once

#include <functional>

#include "../request.h"

class InvalidContentLengthException : public std::exception {};

// continuusly reads a "stream" (sequecnce of strings), and detects when a HTTP message ends, then creates a HTTPMessage object and sends it off to be processed
class HTTPStreamParser {
public:
    typedef std::function<void(HTTPRequest&)> RequestHandler;
    HTTPStreamParser(RequestHandler handler);

    void readNext(const std::string& data);

private:
    std::string _currentLine;
    std::string _buffer;

    int _headerLine; // current line in the header
    int _contentLength;
    bool _readingBody;
    std::string _currentBody;

    HTTPRequest _currentRequest;
    RequestHandler _requestHandler;

    void processHeaderLine();
    void onRequestEnd();
};