#ifndef CONFIG_JSON_UTILS_H_
#define CONFIG_JSON_UTILS_H_

#include <string>
#include <vector>

namespace Config {
struct Token;
class Node;

enum class JsonToken : int {
    // ? {  
    LBrace,     
    // ? }
    RBrace,     
    // ? [      
    LBracket,   
    // ? ]   
    RBracket,   
    // ? :
    Colon,      
    // ? ,
    Comma,      
    Num,
    Bool,
    String,     
    Null
};

class JsonUtil {
public:
    static std::vector<Token> jsonLexer(const std::string& json);
};
}
#endif // CONFIG_JSON_UTILS_H_