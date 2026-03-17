#include <config/Node.h>
#include <stdexcept>

using namespace Config;

Node::Node(NodeType type) : nodeType(type) {};

size_t Node::size() const {
    if (none()) return 0;
    if (isValue()) return isNull() ? 0 : 1;
    return isObject() ? obj.size() : arr.size();
}

NodeType Node::type() const {
    return nodeType;
}

bool Node::isValue() const {
    return type() == NodeType::Value;
}

bool Node::isObject() const {
    return type() == NodeType::Object;
}

bool Node::isArray() const {
    return type() == NodeType::Array;
}

bool Node::none() const {
    return type() == NodeType::None;
}

Node& Node::asValue() {
    if (none()) nodeType = NodeType::Value;
    if (!isValue()) 
        throw std::runtime_error("Node: type is not equal None or Value");
    return *this;
}

Node& Node::asObject() {
    if (none()) nodeType = NodeType::Object;
    if (!isObject())
        throw std::runtime_error("Node: type is not equal None or Object");
    return *this;
}

Node& Node::asArray() {
    if (none()) nodeType = NodeType::Array;
    if (!isArray())
        throw std::runtime_error("Node: type is not None or Array");
    return *this;
}