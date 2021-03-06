#pragma once

#include <string>
#include <vector>
#include <unordered_map>

namespace ROK::API {

typedef std::unordered_map<std::string, std::string> PathVariables;

class ResourcePath {
public:

    bool operator==(const ResourcePath& other);

    ResourcePath& addPart(const std::string& name, bool isVar = false);

    PathVariables matchAndGetVars(std::string& path);

private:
    struct PathPoint {
        std::string name;
        bool isVar;
    };

    std::vector<PathPoint> _path;

};

};