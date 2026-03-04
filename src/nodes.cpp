#include <config/nodes.hpp>

#include <string>

using namespace Config;

std::string ValueNode::getValue() {
    return value;
}

std::unordered_map<std::string, std::shared_ptr<Node>> ObjectNode::getValue() {
    return fields;
}

std::vector<std::shared_ptr<Node>> ArrayNode::getValue() {
    return elements;
}