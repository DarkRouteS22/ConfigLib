#include "config/Node.h"

#include <cstdint>
#include <optional>
#include <stdexcept>
#include <string>
#include <variant>

using namespace Config;

bool Node::isNull() const {
    return !value_data_;
}

bool Node::isString() const {
    if (isNull()) return false;
    return std::holds_alternative<std::string>(*value_data_);    
}

bool Node::isInt() const {    
    if (isNull()) return false;
    return std::holds_alternative<int64_t>(*value_data_);  
}

bool Node::isFloat() const {
    if (isNull()) return false;
    return std::holds_alternative<double>(*value_data_);  
}

bool Node::isBool() const {
    if (isNull()) return false;
    return std::holds_alternative<bool>(*value_data_);  
}

Node& Node::operator=(std::optional<value_data> value) {
    value_data_ = value;
    return *this;
}

Node& Node::operator=(std::string value) {
    value_data_ = std::make_optional<value_data>(value);
    return *this;
}

Node& Node::operator=(int64_t value) {
    value_data_ = std::make_optional<value_data>(value);
    return *this;
}

Node& Node::operator=(double value) {
    value_data_ = std::make_optional<value_data>(value);
    return *this;
}

Node& Node::operator=(bool value) {
    value_data_ = std::make_optional<value_data>(value);
    return *this;
}

Node& Node::operator=(std::nullopt_t) {
    value_data_ = std::nullopt;
    return *this;
}

Node& Node::set(std::optional<value_data> value) {return (*this) = value;}
Node& Node::set(std::string value) {return (*this) = value;}
Node& Node::set(int64_t value) {return (*this) = value;}
Node& Node::set(double value) {return (*this) = value;}
Node& Node::set(bool value) {return (*this) = value;}
Node& Node::set(std::nullopt_t value) {return (*this) = value;}

std::optional<value_data> Node::getValue() const {
    return value_data_;
}

std::string Node::getString() const {
    if (!isValue()) throw std::runtime_error("Not Node a Value");
    if (!isString()) throw std::runtime_error("Node Value in Not a String");
    return std::get<std::string>(*value_data_);
}
int64_t Node::getInt() const {
    if (!isValue()) throw std::runtime_error("Not Node a Value");
    if (!isInt()) throw std::runtime_error("Node Value in Not an Int");
    return std::get<int64_t>(*value_data_);
}
double Node::getFloat() const {
    if (!isValue()) throw std::runtime_error("Not Node a Value");
    if (!isFloat()) throw std::runtime_error("Node Value in Not a Float");
    return std::get<double>(*value_data_);
}
bool Node::getBool() const {
    if (!isValue()) throw std::runtime_error("Not Node a Value");
    if (!isBool()) throw std::runtime_error("Node Value in Not a Bool");
    return std::get<bool>(*value_data_);
}