#ifndef CONFIG_UTIL_H_
#define CONFIG_UTIL_H_

#include <string>
#include <variant>

namespace Config {
enum class JsonToken : int;

using value = std::variant<std::string, long, bool, double, std::nullptr_t>;

struct Token {
    // todo: реализовать для любого типа в будущем
    JsonToken type; 
    std::string value;
    size_t line = 0;
    size_t column = 0;
};

class Util {
public:
    static void parseError(const std::string& msg, Token token);
    static bool isValue(JsonToken type);
    static value parseValue(Token token);
};

}
#endif // CONFIG_UTIL_H_