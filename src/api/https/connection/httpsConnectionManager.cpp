#include "httpsConnectionManager.h"

#include "httpsConnection.h"

HTTPSConnectionManager::HTTPSConnectionManager() {
}

void HTTPSConnectionManager::start(HTTPSConnection* conn) {
    _connections.emplace(conn);
    conn->start();
}

void HTTPSConnectionManager::stop(HTTPSConnection* conn) {
    _connections.erase(conn);
    conn->stop();
}

void HTTPSConnectionManager::stopAll() {
    for(auto conn : _connections)
        conn->stop();

    _connections.clear();
}
