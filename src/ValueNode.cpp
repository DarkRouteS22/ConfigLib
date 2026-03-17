#include <config/Node.h>

using namespace Config;

ValueType Node::valueType() const {
    return valType;
}

bool Node::isNull() const {
    return valueType() == ValueType::Null; 
}

bool Node::isString() const {
    return valueType() == ValueType::String; 
}

bool Node::isInt() const {
    return valueType() == ValueType::Int; 
}

bool Node::isFloat() const {
    return valueType() == ValueType::Float; 
}

bool Node::isBool() const {
    return valueType() == ValueType::Bool; 
}

std::string Node::asString() {
    asValue();
    if (!isString()) valType = ValueType::String;
    return s;
}

int64_t Node::asInt() {
    asValue();
    if (!isInt()) valType = ValueType::Int;
    return data.i;
}

double Node::asFloat() {
    asValue();
    if (!isFloat()) valType = ValueType::Float;
    return data.f;
}

bool Node::asBool() {
    asValue();
    if(!isBool()) valType = ValueType::Bool;
    return data.b;
}

Node& Node::operator=(int i) {
    asInt();
    data.i = i;
    return *this;
}

Node& Node::operator=(bool b) {
    asBool();
    data.b = b;
    return *this;
}

Node& Node::operator=(double f) {
    asFloat();
    data.f = f;
    return *this;
}

Node& Node::operator=(const std::string& str) {
    asString();
    s = str;
    return *this;
}

Node& Node::operator=(const char* str) {
    return *this = std::string(str);
}

Node& Node::set(int i) {
    return *this = i;
}

Node& Node::set(bool b) {
    return *this = b;
}

Node& Node::set(double f) {
    return *this = f;
}

Node& Node::set(const std::string& str) {
    return *this = str;
}

Node& Node::set(const char* str) {
    return *this = str;
}

int64_t Node::tryAsInt(int64_t def) const {
    return (isValue() && isInt()) ? data.i : def;
}

double Node::tryAsFloat(double def) const {
    return (isValue() && isFloat()) ? data.f : def;
}

bool Node::tryAsBool(bool def) const {
    return (isValue() && isBool()) ? data.b : def;
}

const std::string& Node::tryAsString(const std::string& def) const {
    return (isValue() && isString()) ? s : def;
}