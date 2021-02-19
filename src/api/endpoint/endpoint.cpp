#include "endpoint.h"

namespace ROK::API::Endpoint {

Endpoint::Endpoint() {
    _log = spdlog::get("console");
}

};
