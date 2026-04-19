#include "config/parser.h"

#include <string>
#include <vector>

#include "config/Util.h"
#include "config/JsonUtil.h"
#include "config/Node.h"
#include "config/Context.h"


using namespace Config;

Node Json::fromJson(const std::string& json) {
    std::vector<Token> tokens = JsonUtil::jsonLexer(json);
    
    Node root; // корень для возврата
    
    std::vector<Context> stack;
    Context context;

    context.wait = Wait::Value;
    context.parent() = root;

    for (Token token : tokens) {
        switch (context.wait) {
            case Wait::Value: {
                if (token.type == JsonToken::LBrace) {
                    // приводим к объекту
                    context.parent().asObject(); 
                    // ждём элементы объекта
                    context.wait = Wait::Object; 

                    continue;
                }
                if (token.type == JsonToken::LBracket ) {
                    // приводим к массиву
                    context.parent().asArray(); 
                    // ждём элементы массива
                    context.wait = Wait::Array; 

                    continue;
                }
                if (Util::isValue(token.type)) {
                    // todo: приведение к значению. парсинг значения и передача в Node
                }
                Util::parseError("Parser: unexpected token, expected Value, Left Brace or Left Bracket", token);
            }
            case Wait::Object: {
                if (token.type == JsonToken::String) {
                    
                    context.parent() = context.parent()[token.value];
                    context.wait = Wait::AfterKey;
                    
                    continue;
                }
                if (token.type == JsonToken::RBrace) {
                    
                    context.wait = Wait::None;
                    
                    continue;
                }
                Util::parseError("Parser: unexpected token, expected Key or Right Brace", token);
                break;
            }  
            case Wait::Array: {
                if (Util::isValue(token.type)) {}
                if (token.type == JsonToken::RBracket) {}
                Util::parseError("Parser: unexpected token, expected Value or Right Bracket", token);
                break;
            }
            case Wait::AfterKey: {
                if (token.type == JsonToken::Colon) {}
                Util::parseError("Parser: unexpected token, expected Colon", token);
                break;
            }
            case Wait::AfterOValue: {
                if (token.type == JsonToken::Comma) {}
                if (token.type == JsonToken::RBrace) {}
                Util::parseError("Parser: unexpected token, expected Comma or Right Brace", token);
                break;
            }
            case Wait::AfterAValue: {
                if (token.type == JsonToken::Comma) {
                    context.wait = Wait::Value;   
                }
                if (token.type == JsonToken::RBracket) {}
                Util::parseError("Parser: unexpected token, expected Comma or Right Bracket", token);
                break;
            }
            default: {
                if (stack.size() == 1) return root;
                context = stack.back();
                stack.pop_back();
            }
        }
    }

    return root;
} 
