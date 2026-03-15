#include "config/manager.hpp"
#include <config/parser.hpp>
#include <cstddef>

using namespace Config;

enum Token {
    LBrace,     // ? {  
    RBrace,     // ? }
    LBracker,   // ? [   
    RBraker,    // ? ]   
    Colon,      // ? :
    Comma,      // ? ,
    Int,    
    Float,  
    True,   
    False,  
    Str,    
    Null    
};

Node* Parser::fromJson(Manager& manager, const std::string& json) {
    
    return nullptr;
}