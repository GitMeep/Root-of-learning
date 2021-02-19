#pragma once

#include <string>
#include <vector>
#include <unordered_map>

class EndpointPath {
public:
    typedef std::unordered_map<std::string, std::string> PathVariables;

    bool operator==(const EndpointPath& other);

    EndpointPath& addPart(const std::string& name, bool isVar);

    PathVariables matchAndGetVars(std::string& path);

private:
    struct PathPoint {
        std::string name;
        bool isVar;
    };

    std::vector<PathPoint> _path;

};