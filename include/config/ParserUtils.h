#ifndef CONFIG_PARSER_UTILS_H_
#define CONFIG_PARSER_UTILS_H_

#include "config/parser.h"
#include <string>
#include <vector>

namespace Config {
    
struct Token;
class Node;

enum class Wait {
    Value,          
// * Ожидание Значения: { [ str num bool 
    Object,         
// * Ожидание Значени объекта: ключ или }
    Array,          
// * Ожидание Значений объекта: ждём значение или ]
    AfterKey,       
// * Ожидание После ключа: ждём :
    AfterOValue, 
// * Ожидание После Значения Объекта: ждём , или }
    AfterAValue,    
// * Ожидание После Значения Массива: ждём , или ]
    None
};

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
    JsonUtil::JsonToken type; // ! сделать через std::variant
    std::string value;
    size_t line = 0;
    size_t column = 0;
};

struct Context {
    Wait wait;
    std::string key;
    Node* parent;
};

class Util {
public:
    static void parseError(const std::string& msg, Token token);
    static bool isValue(JsonUtil::JsonToken type);
};

}
#endif // CONFIG_PARSER_UTILS_H_