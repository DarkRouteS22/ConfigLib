#include "config/Node.h"

#include <stdexcept>
#include <utility>
#include <vector>
#include <unordered_map>

using namespace Config;

Node::Node() {}

Node::Node(NodeType type) : node_type_(type) {};

Node& Node::operator=(Node node) {
    std::swap(node_type_, node.node_type_);
    std::swap(value_data_, node.value_data_);
    std::swap(array_data_, node.array_data_);
    std::swap(object_data_, node.object_data_);

    return *this;
}


size_t Node::size() const {
    if (isArray() || isObject()) 
        return isArray() ? array_data_.size() : object_data_.size();
    else return 0;
}

NodeType Node::nodeType() const {
    return node_type_;
}

bool Node::isValue() const {
    return node_type_ == NodeType::Value;
}

bool Node::isObject() const {
    return node_type_ == NodeType::Object;
}

bool Node::isArray() const {
    return node_type_ == NodeType::Array;
}

bool Node::isNone() const {
    return node_type_ == NodeType::None;
}

Node& Node::asValue() {
    if (isValue() || isNone()) node_type_ = NodeType::Value;
    else std::runtime_error("Node type not equal None or Value");
    return *this;
}

Node& Node::asObject() {
    if (isObject() || isNone()) node_type_ = NodeType::Object;
    else std::runtime_error("Node type not equal None or Object");
    return *this;
}

Node& Node::asArray() {
    if (isArray() || isNone()) node_type_ = NodeType::Array;
    else std::runtime_error("Node type not equal None or Array");
    return *this;
}