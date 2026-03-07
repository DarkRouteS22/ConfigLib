#include <config/nodes.hpp>

using namespace Config;

const std::string& ValueNode::getValue() const {
    return value;
}

void ValueNode::set(const std::string& value, ValueType type) {
    this->value = value;
    this->vtype = type;
}

NodeType ValueNode::type() const {
    return NodeType::ValueNode;
}