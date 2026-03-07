#include <config/nodes.hpp>

using namespace Config;

std::vector<Node*>& ArrayNode::getValue() {
    return elements;
}

void ArrayNode::add(Node* node) {
    elements.push_back(node);
}

void ArrayNode::set(const std::vector<Node*> elements) {
    this->elements = elements;
}

size_t ArrayNode::size() const {
    return elements.size();
}

NodeType ArrayNode::type() const {
    return NodeType::ArrayNode;
}