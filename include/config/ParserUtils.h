#ifndef CONFIG_PARSERUTILS_H_
#define CONFIG_PARSERUTILS_H_

#include <string>
#include <vector>

namespace Config {
struct Token;

class JsonUtil {
public:
    enum class JsonToken {
        LBrace,     // ? {  
        RBrace,     // ? }
        LBracket,   // ? [   
        RBracket,   // ? ]   
        Colon,      // ? :
        Comma,      // ? ,
        Num,
        Bool,
        String,     
        Null
    };

    static std::vector<Token> jsonLexer(const std::string& json);
};

struct Token {
    JsonUtil::JsonToken type; // todo: переделать через std::variant
    std::string value;
    size_t line = 0;
    size_t column = 0;
};

class Util {
public:
    static void parseError(const std::string& msg, Token token);
};

}
#endif // CONFIG_PARSERUTILS_H_