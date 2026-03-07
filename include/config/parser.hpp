#ifndef CONFIG_PARSER_HPP
#define CONFIG_PARSER_HPP

#include <config/nodes.hpp>
#include <config/manager.hpp>

namespace Config {


class Parser {
public:
    enum Type {
        JSON,
    };
    Parser(Type, Manager&);
    Node* toNode(const std::string&);
    std::string toString(const Node*);
private:
    Type type;
};

}
#endif