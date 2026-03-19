#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <config/Node.h>
#include <vector>

namespace Config {

class Parser {
public:
    static Node fromJson(const std::string&);
    static Node fromJson(const std::vector<std::string>&);
    static Node readJson(const std::string&);
    static std::string fromJson(const Node&);

private:
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

    struct Token {
        union {
            JsonToken json;
        } type;
        std::string value;
        size_t line = 0;
        size_t column = 0;
    };

    static std::vector<Token> lexer(const std::string&);
};

}
#endif