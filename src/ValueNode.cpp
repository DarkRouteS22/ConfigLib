#include "config/Node.h"

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>

#include <iostream>

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
    // ! DEBUG
    std::cout << "on str" << "\n";
    std::cout << ToString(nodeType()) << "\n";

    throw std::runtime_error("Node: mismatch of types");
}

long Node::asInt() const {
    if (isInt()) return value_data_.int_value_;
    // ! DEBUG
    std::cout << "on int" << "\n";
    throw std::runtime_error("Node: mismatch of types");
}

double Node::asFloat() const {
    if (isFloat()) return value_data_.float_value_;
    // ! DEBUG
    std::cout << "on float" << "\n";
    throw std::runtime_error("Node: mismatch of types");
}

bool Node::asBool() const {
    if (isBool()) return value_data_.bool_value_;
    // ! DEBUG
    std::cout << "on bool" << "\n";
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

void Node::operator=(long intValue) {
    toInt();
    value_data_.int_value_ = intValue;
}

void Node::operator=(bool boolValue) {
    toBool();
    value_data_.bool_value_ = boolValue;
}

void Node::operator=(double floatValue) {
    toFloat();
    value_data_.float_value_ = floatValue;
}

void Node::operator=(const std::string& str) {
    toString();
    string_value_ = str;
}

void Node::operator=(const char* str) {
    *this = std::string(str);
}


Node& Node::setInt(long intValue) {
    *this = intValue;
    return *this;
}

Node& Node::setBool(bool boolValue) {
    *this = boolValue;
    return *this;
}

Node& Node::setFloat(double floatValue) {
    *this = floatValue;
    return *this;
}

Node& Node::setString(const std::string& str) {
    *this = str;
    return *this;
}

Node& Node::setString(const char* str) {
    *this = str;
    return *this;
}

long Node::tryAsInt(long def) const {
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

void Node::operator=(std::nullptr_t) {
    node_type_ = NodeType::Value;
    value_type_ = ValueType::Null;
}

Node& Node::setNull() {
    node_type_ = NodeType::Value;
    value_type_ = ValueType::Null;
    return *this;
}