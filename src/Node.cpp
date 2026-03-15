#include <config/nodes.hpp>
#include <optional>
#include <stdexcept>

using namespace Config;

Node& Node::operator[](const std::string& key) {
    return asObject()[key];
}

ObjectNode& Node::asObject() {
    if (type() == NodeType::ObjectNode) 
        return static_cast<ObjectNode&>(*this);
    throw std::runtime_error("Node: not an objec");
}

const ObjectNode& Node::asObject() const{
    if (type() == NodeType::ObjectNode) 
        return static_cast<const ObjectNode&>(*this);
    throw std::runtime_error("Node: not an object");
}

ValueNode& Node::asValue() {
    if (type() == NodeType::ValueNode) 
        return static_cast<ValueNode&>(*this);
    throw std::runtime_error("Node: not a value");
}

const ValueNode& Node::asValue() const {
    if (type() == NodeType::ValueNode) 
        return static_cast<const ValueNode&>(*this);
    throw std::runtime_error("Node: not a value");
}

ArrayNode& Node::asArray() {
    if (type() == NodeType::ArrayNode) 
        return static_cast<ArrayNode&>(*this);
    throw std::runtime_error("Node: not an array");
}

const ArrayNode& Node::asArray() const {
    if (type() == NodeType::ArrayNode) 
        return static_cast<const ArrayNode&>(*this);
    throw std::runtime_error("Node: not an array");
}

ObjectNode* Node::tryAsObject() {
    if (type() == NodeType::ObjectNode) 
        return static_cast<ObjectNode*>(this);
    return nullptr;
}

ValueNode* Node::tryAsValue() {
    if (type() == NodeType::ObjectNode) 
        return static_cast<ValueNode*>(this);
    return nullptr;
}

ArrayNode* Node::tryAsArray() {
    if (type() == NodeType::ObjectNode) 
        return static_cast<ArrayNode*>(this);
    return nullptr;
}