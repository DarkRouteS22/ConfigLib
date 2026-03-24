#include "config/Node.h"

#include <stdexcept>
#include <vector>

using namespace Config;

Node& Node::operator[](size_t i) {
    asArray();
    if (i >= size()) 
        array_value_.resize(i + 1);
    return array_value_.at(i);
}

Node& Node::at(size_t i) {
    asArray();
    if (i >= size()) 
        throw std::out_of_range("Node: out uf range ib array");
    return array_value_.at(i);
}

Node& Node::add() {
    asArray();
    array_value_.emplace_back();
    return array_value_.back();
}

std::vector<Node>::iterator Node::begin() {
    if (!isArray()) throw std::runtime_error("Node is not Array");
    return array_value_.begin();
}

std::vector<Node>::iterator Node::end() {
    if (!isArray()) throw std::runtime_error("Node is not Array");
    return array_value_.end();
}