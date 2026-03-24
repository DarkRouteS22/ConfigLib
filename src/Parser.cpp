#include "config/parser.h"

#include <string>
#include <vector>

#include "config/Node.h"
#include "config/ParserUtils.h"

using namespace Config;

Node JsonParser::fromJson(const std::vector<std::string>& json_array) {
    std::string json_string = "";
    for (std::string str : json_array) {
        json_string += str + "\n";
    }
    
    return fromJson(json_string);
}

Node JsonParser::fromJson(const std::string& json_string) {
    std::vector<Token> tokens = JsonUtil::jsonLexer(json_string); // получаем токены

    std::string current_path = ""; // текущее положение в root узле
    Node root; // root узел

    return root;
}
