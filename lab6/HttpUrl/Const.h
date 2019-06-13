#pragma once
#include <string>

const std::string INVALID_PROTOCOL = "Invalid protocol";
const std::string INVALID_DOMAIN = "Invalid domain";
const std::string INVALID_PORT = "Invalid port";
const std::string INVALID_DOCUMENT = "Invalid document";
const std::string CONST_HTTP = "http";
const std::string CONST_HTTPS = "https";
const int STANDARD_PORT_FOR_HTTP = 80;
const int STANDARD_PORT_FOR_HTTPS = 443;
const int MIN_PORT = 1;
const int MAX_PORT = 49151;
const std::string EMPTY_DOMAIN = "Empty domain";
const std::string EMPTY_DOCUMENT = "Empty document";
const std::string DOMAIN_REGEX = R"(^([[:alnum:]-\\.]+)$)";