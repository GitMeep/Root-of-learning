#include "streamParser.h"

#include <sstream>

HTTPStreamParser::HTTPStreamParser(RequestHandler handler) {
    _headerLine = 1;
    _contentLength = -1;
    _readingBody = false;

    _currentLine = "";
    _currentBody = "";

    _requestHandler = handler;
}

void HTTPStreamParser::readNext(const std::string& data) {
    _buffer += data;
    if(!_readingBody) {
        std::string line;
        bool linesLeft = true;
        bool lineFound;
        while(linesLeft) {
            line = "";
            int newlinePos = _buffer.find_first_of('\n');
            if(newlinePos == std::string::npos) {
                line = _buffer;
                _buffer = "";
                lineFound = false;
            } else {
                lineFound = true;
                line = _buffer.substr(0, newlinePos);
                _buffer = _buffer.substr(newlinePos + 1); // +1: remove newline character
            }
            line.erase( std::remove(line.begin(), line.end(), '\r'), line.end() ); // nuke carriage returns from orbit
            _currentLine += line;
            if(lineFound) { // endline was met
                if(_currentLine == "") { // empty line, means body should be read now
                    if(_contentLength == -1) { // no content length, but body was started, this is the end of the request
                        onRequestEnd();
                    } else {
                        _readingBody = true;
                        linesLeft = false;
                    }
                } else { // just the end of a normal header line
                    processHeaderLine();
                }
            } else { // no more lines left in the buffer
                linesLeft = false;
            }
        }
    }

    if(_readingBody) {
        _currentBody += _buffer;
        _buffer = "";
        if(_currentBody.length() >= _contentLength) { // full body has been read
            std::string leftover = _currentBody.substr(_contentLength);
            _currentBody = _currentBody.substr(0, _contentLength);
            _buffer += leftover;
            
            _currentRequest.setBody(_currentBody);
            onRequestEnd();
        }
    }
}

void HTTPStreamParser::onRequestEnd() {
    _requestHandler(_currentRequest);

    _headerLine = 1;
    _contentLength = -1;
    _readingBody = false;
    _currentBody = "";
}

void HTTPStreamParser::processHeaderLine() {
    if(_headerLine == 1) {
        int slashPos = _currentLine.find_first_of('/');
        if(slashPos == std::string::npos) {
            _currentRequest.setMethod(HTTPRequest::GET);
        } else {
            std::stringstream ss;
            ss << _currentLine;
            std::string method, path, version;
            ss >> method >> path >> version;
            version = version.substr(version.find_first_of('/')+1);
            _currentRequest.setMethod(method);
            _currentRequest.setPath(path);
            _currentRequest.setVersion(version);
        }
    } else {
        std::string key, value;
        int colonPos = _currentLine.find_first_of(':');
        if(colonPos != std::string::npos) {
            key = _currentLine.substr(0, colonPos);
            value = _currentLine.substr(colonPos + 2); // remove both colon and space
            _currentRequest.setHeader(key, value);

            if(key == "Content-Length") {
                try {
                    _contentLength = std::stoi(value);
                } catch(std::exception& e) {
                    throw InvalidContentLengthException();
                }
                
            }
        } // just ignore it if it's not valid
    }

    _currentLine = "";
    _headerLine++;
}
