#ifndef CONFIG_PARSER_H_
#define CONFIG_PARSER_H_

#include <string>
#include <vector>

namespace Config {

enum class JsonToken;
class Node;

class Json {
public:
    static Node fromJson(const std::string&);
    static Node fromJson(const std::vector<std::string>&);
    static std::string toJson(const Node&);
};

}
#endif // CONFIG_PARSER_H_