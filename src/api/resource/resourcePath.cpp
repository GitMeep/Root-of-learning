#include "resourcePath.h"

#include <sstream>

namespace ROK::API {

ResourcePath& ResourcePath::addPart(const std::string& name, bool isVar) {
    PathPoint pp;
    pp.isVar = isVar;
    pp.name = name;
    _path.emplace_back(pp);
    return *this;
}

PathVariables ResourcePath::matchAndGetVars(std::string& path) {
    std::stringstream ss;
    ss << path.substr(1); // remove leading /

    PathVariables vars;

    int it = 0;
    bool match = false;
    std::string part;
    while(std::getline(ss, part, '/')) {
        if(_path[it].isVar) {
            vars[_path[it].name] = part;
            match = true;
        } else {
            if(_path[it].name != part) {
                match = false;
                break;
            }
        }
        it++;
    }

    if(!match) {
        return {{"no match", ""}};
    }

    return vars;
}

bool ResourcePath::operator==(const ResourcePath& other) {
    if(_path.size() != other._path.size()) return false;

    for(int i = 0; i < _path.size(); i++) {
        if(_path[i].name != other._path[i].name || _path[i].isVar != other._path[i].isVar) return false;
    }

    return true;
}

};
