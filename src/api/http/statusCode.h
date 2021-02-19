#pragma once

#include <string>
#include <vector>

class HTTPStatusCode {
public:
    enum Status {
        CONTINUE,
        SWITCHING_PROTOCOL,
        PROCESSING,
        EARLY_HINTS,

        OK,
        CREATED,
        ACCEPTED,
        NON_AUTHORATIVE_INFORMATION,
        NO_CONTENT,
        RESET_CONTENT,
        PARTIAL_CONTENT,
        MULTI_STATUS,
        ALREADY_REPORTED,
        IM_USED,

        MULTIPLE_CHOICE,
        MOVED_PERMANENTLY,
        FOUND,
        SEE_OTHER,
        NOT_MODIFIED,
        TEMPORARY_REDIRECT,
        PERMANENT_REDIRECT,

        BAD_REQUEST,
        UNAUTHORIZED,
        PAYMENT_REQUIRED,
        FORBIDDEN,
        NOT_FOUND,
        METHOD_NOT_ALLOWED,
        PROXY_AUTHENTICATION_REQUIRED,
        REQUEST_TIMEOUT,
        CONFLICT,
        GONE,
        LENGTH_REQUIRED,
        PRECONDITION_FAILED,
        PAYLOAD_TOO_LARGE,
        URI_TOO_LONG,
        UNSUPPORTED_MEDIA_TYPE,
        RANGE_NOT_SATISFIABLE,
        EXPECTATION_FAILED,
        IM_A_TEAPOT,
        MISDIRECTED_REQUEST,
        UNRPOCESSABLE_ENTITY,
        LOCKED,
        FAILED_DEPENDENCY,
        TOO_EARLY,
        PRECONDITION_REQUIRED,
        TOO_MANY_REQUESTS,
        REQUEST_HEADER_FIELDS_TOO_LARGE,
        UNAVAILABLE_FOR_LEGAL_REASONS,
        
        INTERNAL_SERVER_ERROR,
        NOT_IMPLEMENTED,
        BAD_GATEWAY,
        SERVICE_UNAVAILABLE,
        GATEWAY_TIMEOUT,
        HTTP_VERSION_NOT_SUPPORTED,
        VARIANT_ALSO_NEGOTIATES,
        INSUFFICIENT_STORAGE,
        LOOP_DETECTED,
        NOT_EXTENDED,
        NETWORK_AUTHENTICATION_REQUIRED
    };

    HTTPStatusCode();
    HTTPStatusCode(Status status);

    std::string getString();
    static std::string getString(const Status& status);

private:
    Status _status;

    static std::vector<std::string> _strings;
};
