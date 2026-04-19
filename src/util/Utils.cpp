#include "config/Util.h"

#include <stdexcept>
#include <string>

#include "config/JsonUtil.h"

using namespace Config; 

void Util::parseError(const std::string &msg, Token token) {
    throw std::runtime_error(
        msg + "\n" +
        "at Line: " + std::to_string(token.line) +
        " Column: " + std::to_string(token.column)
    );
}

bool Util::isValue(JsonToken type) {
    return type == JsonToken::String ||
           type == JsonToken::Num    ||
           type == JsonToken::Bool   ||
           type == JsonToken::Null;
}

