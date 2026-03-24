#include "config/Node.h"

#include <cstdint>
#include <stdexcept>
#include <string>

using namespace Config;

ValueType Node::valueType() const {
    return value_type_;
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

std::string Node::asString() const {
    if (isString()) return string_value_;
    throw std::runtime_error("Node: mismatch of types");
}

int64_t Node::asInt() const {
    if (isInt()) return value_data_.int_value_;
    throw std::runtime_error("Node: mismatch of types");
}

double Node::asFloat() const {
    if (isFloat()) return value_data_.float_value_;
    throw std::runtime_error("Node: mismatch of types");
}

bool Node::asBool() const {
    if (isBool()) return value_data_.bool_value_;
    throw std::runtime_error("Node: mismatch of types");
}

Node& Node::toString() {
    asValue();
    if (!isString()) value_type_ = ValueType::String;
    return *this;
}

Node& Node::toInt() {
    asValue();
    if (!isInt()) value_type_ = ValueType::Int;
    return *this;
}

Node& Node::toFloat() {
    asValue();
    if (!isFloat()) value_type_ = ValueType::Float;
    return *this;
}

Node& Node::toBool() {
    asValue();
    if(!isBool()) value_type_ = ValueType::Bool;
    return *this;
}

void Node::operator=(int64_t intValue) {
    asInt();
    value_data_.int_value_ = intValue;
}

void Node::operator=(bool boolValue) {
    asBool();
    value_data_.bool_value_ = boolValue;
}

void Node::operator=(double floatValue) {
    asFloat();
    value_data_.float_value_ = floatValue;
}

void Node::operator=(const std::string& str) {
    asString();
    string_value_ = str;
}

void Node::operator=(const char* str) {
    *this = std::string(str);
}

void Node::operator=(int value) {
    value_data_.int_value_ = value;
}


Node& Node::set(int64_t intValue) {
    *this = intValue;
    return *this;
}

Node& Node::set(bool boolValue) {
    *this = boolValue;
    return *this;
}

Node& Node::set(double floatValue) {
    *this = floatValue;
    return *this;
}

Node& Node::set(const std::string& str) {
    *this = str;
    return *this;
}

Node& Node::set(const char* str) {
    *this = str;
    return *this;
}

int64_t Node::tryAsInt(int64_t def) const {
    return (isValue() && isInt()) ? value_data_.int_value_ : def;
}

double Node::tryAsFloat(double def) const {
    return (isValue() && isFloat()) ? value_data_.float_value_ : def;
}

bool Node::tryAsBool(bool def) const {
    return (isValue() && isBool()) ? value_data_.bool_value_ : def;
}

const std::string& Node::tryAsString(const std::string& def) const {
    return (isValue() && isString()) ? string_value_ : def;
}