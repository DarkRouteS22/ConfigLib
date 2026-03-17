#include <config/Node.h>
#include <stdexcept>

using namespace Config;

Node& Node::operator[](size_t i) {
    asArray();
    if (i >= size()) 
        arr.resize(i + 1);
    return arr.at(i);
}

Node& Node::at(size_t i) {
    asArray();
    if (i >= size()) 
        throw std::out_of_range("Node: out uf range ib array");
    return arr.at(i);
}

Node& Node::add() {
    asArray();
    arr.emplace_back();
    return arr.back();
}