#include "config/Node.h"
#include <cctype>
#include <config/parser.h>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <iostream>

using namespace Config;

Node Parser::fromJson(const std::string& json) {
    
}

std::vector<Parser::Token> Parser::lexer(const std::string& str) {
    std::vector<Parser::Token> result;
    size_t line = 1;
    size_t col = 0;
    for (size_t index = 0; index < str.length(); index++) {
        Token token;
        token.line = line;
        col++;

        switch (str[index]) {
            case '{': {
                token.type.json = JsonToken::LBrace;
                token.column = col;

                token.value += str[index];

                result.emplace_back(token);
                continue;
            }
            case '}': {
                token.type.json = JsonToken::RBrace;
                token.column = col;

                token.value += str[index];

                result.emplace_back(token);
                continue;
            }
            case '[': {
                token.type.json = JsonToken::LBracket;
                token.column = col;

                token.value += str[index];

                result.emplace_back(token);
                continue;
            }
            case ']': {
                token.type.json = JsonToken::RBracket;
                token.column = col;

                token.value += str[index];

                result.emplace_back(token);
                continue;
            }
            case ':': {
                token.type.json = JsonToken::Colon;
                token.column = col;

                token.value += str[index];

                result.emplace_back(token);
                continue;
            }
            case ',': {
                token.type.json = JsonToken::Comma;
                token.column = col;

                token.value += str[index];

                result.emplace_back(token);
                continue;
            }
        }

        if (str[index] == '"') {
            token.type.json = JsonToken::String;
            token.column = col;

            index ++;
            while (str[index] != '"') {
                if (str[index] == '\\' &&  str[index + 1] == '"') {
                    index ++;
                } 
                token.value += str[index];
                index ++;
                if (index > str.length()) {
                    throw std::runtime_error("unlim str");
                }

            }
            result.emplace_back(token);
        }

        if (std::isdigit(str[index]) || str[index] == '-') {
            token.type.json = JsonToken::Num;
            token.column = col;
            token.value += str[index];
            index++;
            while (std::isdigit(str[index]) || str[index] == '.') {
                token.value += str[index];
                index++;
            }
            result.emplace_back(token);
            continue;
        }
        
        if (str[index] == 'n') {
            token.column = col;
            index += 3;
            token.type.json = JsonToken::Null;
            result.emplace_back(token);
            continue;
        }

        if (str[index] == 't') {
            token.column = col;
            index += 3;
            token.type.json = JsonToken::Bool;
            token.value = "true";
            result.emplace_back(token);
            continue;
        }

        if (str[index] == 'f') {
            token.column = col;
            index += 4;
            token.type.json = JsonToken::Bool;
            token.value = "false";
            result.emplace_back(token);
            continue;
        }
        
        if (str[index] == '\n') {
            line++;
            col = 0;
            continue;
        }  
    }
    return result;
}
