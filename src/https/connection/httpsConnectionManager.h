#pragma once

#include <set>

class HTTPSConnection;

class HTTPSConnectionManager {
public:
    HTTPSConnectionManager();

    void start(HTTPSConnection* conn);
    void stop(HTTPSConnection* conn);

    void stopAll();

private:
    std::set<HTTPSConnection*> _connections;

};