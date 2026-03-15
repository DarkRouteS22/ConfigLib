#include <config/nodes.hpp>
#include <stdexcept>

using namespace Config;

size_t ArrayNode::size() const {
    return elements.size();
}

NodeType ArrayNode::type() const {
    return NodeType::ArrayNode;
}

Node& ArrayNode::operator[](unsigned int index) {
    if (index >= size())
        throw std::out_of_range("ArrayNode: index out of range");
    return *elements[index];
}

Node& ArrayNode::at(unsigned int index) {
    return (*this)[index];
}

Node& ArrayNode::add(Node& node) {
    elements.push_back(&node);
    return node;
}