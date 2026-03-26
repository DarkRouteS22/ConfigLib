#include "config/Node.h"

#include <stdexcept>
#include <vector>
#include <unordered_map>

#include <iostream>

using namespace Config;

Node::Node(NodeType type) : node_type_(type) {};

size_t Node::size() const {
    if (isNone()) return 0;
    if (isValue()) return isNull() ? 0 : 1;
    return isObject() ? object_value_.size() : array_value_.size();
}

NodeType Node::nodeType() const {
    return node_type_;
}

bool Node::isValue() const {
    return nodeType() == NodeType::Value;
}

bool Node::isObject() const {
    return nodeType() == NodeType::Object;
}

bool Node::isArray() const {
    return nodeType() == NodeType::Array;
}

bool Node::isNone() const {
    return nodeType() == NodeType::None;
}

Node& Node::asValue() {
    if (isNone()) node_type_ = NodeType::Value;
    if (!isValue()) 
        throw std::runtime_error("Node: type is not equal None or Value");
    return *this;
}

Node& Node::asObject() {
    if (isNone()) node_type_ = NodeType::Object;
    // ! DEBUG
    std::cout << ToString(nodeType()) << "\n";

    if (!isObject())
        throw std::runtime_error("Node: type is not equal None or Object");
    return *this;
}

Node& Node::asArray() {
    if (isNone()) node_type_ = NodeType::Array;
    if (!isArray())
        throw std::runtime_error("Node: type is not None or Array");
    return *this;
}