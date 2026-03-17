#ifndef CONFIG_PARSER_HPP
#define CONFIG_PARSER_HPP

#include <config/Nodes.h>

namespace Config {

class Parser {
public:
    static Node& fromJson(const std::string&);
    static std::string fromJson(const Node&);
};

}
#endif