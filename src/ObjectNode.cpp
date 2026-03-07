#include <config/nodes.hpp>

using namespace Config;

std::unordered_map<std::string, Node*>& ObjectNode::getValue() {
    return fields;
}

void ObjectNode::add(const std::string& key, Node* node) {
    fields[key] = node;
}

void ObjectNode::set(const std::unordered_map<std::string, Node*>& fields) {
    this->fields = fields;
}

size_t ObjectNode::size() const {
    return fields.size();
}

NodeType ObjectNode::type() const {
    return NodeType::ObjectNode;
}

bool ObjectNode::contains(const std::string& key) const {
    return (fields.find(key) != fields.end());
}

void ObjectNode::remove(const std::string& key) {
    fields.erase(key);
}