#ifndef CONFIG_PARSER_HPP
#define CONFIG_PARSER_HPP

#include <config/nodes.hpp>
#include <config/manager.hpp>

namespace Config {


class Parser {
public:
    static Node* fromJson(Manager&, const std::string&);
    static std::string toJson(const Node*);
};

}
#endif