#include "config/ParserUtils.h"

#include <stdexcept>
#include <string>
#include <vector>

using namespace Config; 

void Util::parseError(const std::string &msg, Token token) {
    throw std::runtime_error(
        msg + "\n" +
        "at Line: " + std::to_string(token.line) +
        " Column: " + std::to_string(token.column)
    );
}

std::vector<Token> JsonUtil::jsonLexer(const std::string& json_string) {
    std::vector<Token> tokens;

    size_t current_line = 1;
    size_t current_column = 1;
    for (size_t index = 0; index < json_string.length(); index++) {
        Token token;
        token.line = current_line;
        current_column++;

        switch (json_string[index]) {
            case '{': {
                token.type = JsonToken::LBrace;
                token.column = current_column;
                token.value += json_string[index];
                tokens.emplace_back(token);
                continue;
            }
            case '}': {
                token.type = JsonToken::RBrace;
                token.column = current_column;
                token.value += json_string[index];
                tokens.emplace_back(token);
                continue;
            }
            case '[': {
                token.type = JsonToken::LBracket;
                token.column = current_column;
                token.value += json_string[index];
                tokens.emplace_back(token);
                continue;
            }
            case ']': {
                token.type = JsonToken::RBracket;
                token.column = current_column;
                token.value += json_string[index];
                tokens.emplace_back(token);
                continue;
            }
            case ':': {
                token.type = JsonToken::Colon;
                token.column = current_column;
                token.value += json_string[index];
                tokens.emplace_back(token);
                continue;
            }
            case ',': {
                token.type = JsonToken::Comma;
                token.column = current_column;
                token.value += json_string[index];
                tokens.emplace_back(token);
                continue;
            }
        }

        if (json_string[index] == '"') {
            token.type = JsonToken::String;
            token.column = current_column;
            index++;
            current_column++;
            while (json_string[index] != '"') {
                if (json_string[index] == '\\' &&  json_string[index + 1] == '"') {
                    index++;
                    current_column++;
                } 
                token.value += json_string[index];
                index++;
                current_column++;
                if (index > json_string.length()) Util::parseError("Lexer: unlim string", token);
            }
            tokens.emplace_back(token);
            continue;
        }

        if (std::isdigit(json_string[index]) || json_string[index] == '-') {
            token.type = JsonToken::Num;
            token.column = current_column;
            token.value += json_string[index];
            index++;
            current_column++;
            while (
                std::isdigit(json_string[index]) || 
                json_string[index] == '.' || 
                json_string[index] == 'e' ||
                json_string[index] == 'E'
            ) {
                token.value += json_string[index];
                index++;
                current_column++;
            }
            tokens.emplace_back(token);
            continue;
        }
        
        if (json_string.substr(index, 4) == "null") {
            token.column = current_column;
            index += 3;
            current_column += 3;
            token.type = JsonToken::Null;
            tokens.emplace_back(token);
            continue;
        }

        if (json_string.substr(index, 4) == "true") {
            token.column = current_column;
            index += 3;
            current_column += 3;
            token.type = JsonToken::Bool;
            token.value = "true";
            tokens.emplace_back(token);
            continue;
        }

        if (json_string.substr(index, 4) == "false") {
            token.column = current_column;
            index += 4;
            current_column += 4;
            token.type = JsonToken::Bool;
            token.value = "false";
            tokens.emplace_back(token);
            continue;
        }
        
        if (json_string[index] == '\n') {
            current_line++;
            current_column = 0;
            continue;
        }

        if (json_string[index] != '\t' && json_string[index] != ' ') {
            Util::parseError("Lexer: unexpected token", token);
        }
    }
    return tokens;
}

bool Util::isValue(JsonUtil::JsonToken type) {
    return type == JsonUtil::JsonToken::String ||
           type == JsonUtil::JsonToken::Num    ||
           type == JsonUtil::JsonToken::Bool   ||
           type == JsonUtil::JsonToken::Null;
}