#ifndef CONFIG_PARSER_HPP
#define CONFIG_PARSER_HPP

#include <config/nodes.hpp>

namespace Config {

class Parser {
public:
    enum Type {
        JSON,
    };
    Parser(Type type);
    std::unique_ptr<Node> parse(const std::string& string);
};

}
#endif