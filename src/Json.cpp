#include "config/ParserUtils.h"
#include "config/parser.h"

#include "config/Node.h"
#include <string>
#include <vector>

using namespace Config;

Node Json::fromJson(const std::string& json) {
    std::vector<Token> tokens = JsonUtil::jsonLexer(json);

    Node root;      // корень для возврата

    std::vector<Context> stack;
    Context waiting;

    waiting.wait = Wait::Value;
    waiting.parent = &root;
    waiting.key = "";

    for (Token token : tokens) {
        switch (waiting.wait) {
            case Wait::Value: {
                if (token.type == JsonUtil::JsonToken::LBrace) {
                    root.asObject();
                    waiting.wait = Wait::Object;
                    continue;
                }
                if (token.type == JsonUtil::JsonToken::LBracket ) {
                    root.asArray();
                    waiting.wait = Wait::Array;
                    continue;
                }
                if (Util::isValue(token.type)) {
                    if (tokens.size() != 1) Util::parseError("Parser: unexpected tokens", token);
                    // return root.asValue().setInt(200);
                }
                Util::parseError("Parser: unexpected token, expected Value, Left Brace or Left Bracket", token);
            }
            case Wait::Object: {
                if (token.type == JsonUtil::JsonToken::String) {
                    waiting.key = token.value;
                    waiting.wait = Wait::AfterKey;
                    continue;
                }
                if (token.type == JsonUtil::JsonToken::RBrace) {
                    waiting.wait = Wait::None;
                    continue;
                }
                Util::parseError("Parser: unexpected token, expected Key or Right Brace", token);
                break;
            }  
            case Wait::Array: {
                if (Util::isValue(token.type)) {}
                if (token.type == JsonUtil::JsonToken::RBracket) {}
                Util::parseError("Parser: unexpected token, expected Value or Right Bracket", token);
                break;
            }
            case Wait::AfterKey: {
                if (token.type == JsonUtil::JsonToken::Colon) {}
                Util::parseError("Parser: unexpected token, expected Colon", token);
                break;
            }
            case Wait::AfterOValue: {
                if (token.type == JsonUtil::JsonToken::Comma) {}
                if (token.type == JsonUtil::JsonToken::RBrace) {}
                Util::parseError("Parser: unexpected token, expected Comma or Right Brace", token);
                break;
            }
            case Wait::AfterAValue: {
                if (token.type == JsonUtil::JsonToken::Comma) {}
                if (token.type == JsonUtil::JsonToken::RBracket) {}
                Util::parseError("Parser: unexpected token, expected Comma or Right Bracket", token);
                break;
            }
            default: {
                if (stack.size() == 1) return root;
                waiting = stack.at(stack.size() - 1);
            }
        }
    }

    return root;
} 
