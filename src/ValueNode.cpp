#include <config/nodes.hpp>
#include <cstdint>
#include <stdexcept>

using namespace Config;

NodeType ValueNode::type() const {
    return NodeType::ValueNode;
}

/*---| set Value function block |---*/
void ValueNode::setInt(int64_t i) {
    data.i = i;
    valType = ValueType::Int;
}

void ValueNode::setBool(bool b) {
    data.b = b;
    valType = ValueType::Bool;
}

void ValueNode::setFloat(double f) {
    data.f = f;
    valType = ValueType::Float;
}

void ValueNode::setString(std::string str) {
    strValue = std::move(str);
    valType = ValueType::String;
}

void ValueNode::setNull() {
    valType = ValueType::Null;
}

/*---| get value type function block |---*/
bool ValueNode::isBool() const {
    return ValueType::Bool == valType;
}

bool ValueNode::isFloat() const {
    return valType == ValueType::Float;
}

bool ValueNode::isInt() const {
    return valType == ValueType::Int;
}

bool ValueNode::isNull() const {
    return valType == ValueType::Null;
}

bool ValueNode::isString() const {
    return valType == ValueType::String;
}

ValueNode::ValueType ValueNode::valueType() const {
    return valType;
}

/*---| get value functions block with exceprion |---*/
int64_t ValueNode::asInt() const {
    if (isInt()) return data.i;
    throw std::runtime_error("ValueNode: not an int");
}

double ValueNode::asFloat() const {
    if (isFloat()) return data.f;
    throw std::runtime_error("ValueNode: not a float");
}

bool ValueNode::asBool() const {
    if (isBool()) return data.b;
    throw std::runtime_error("ValueNode: not a bool");
}

const std::string& ValueNode::asString() const {
    if (isString()) return strValue;
    throw std::runtime_error("ValueNode: not a string");
}

/*---| get value or default functions |--w-*/
int64_t ValueNode::tryAsInt(int64_t i) const {
    return isInt() ? data.i : i;
}

double ValueNode::tryAsFloat(double f) const {
    return isFloat() ? data.f : f;
}

bool ValueNode::tryAsBool(bool b) const {
    return isBool() ? data.b : b;
}

const std::string& ValueNode::tryAsString(const std::string& str) const {
    return isString() ? strValue : str;
}