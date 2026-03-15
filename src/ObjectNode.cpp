#include <config/nodes.hpp>
#include <config/manager.hpp>
#include <stdexcept>

using namespace Config;

size_t ObjectNode::size() const {
    return fields.size();
}

NodeType ObjectNode::type() const {
    return NodeType::ObjectNode;
}

Node& ObjectNode::operator[](const std::string& key) {
    return *(fields[key]);
}

Node& ObjectNode::at(const std::string& key) {
    auto it = fields.find(key);
    if (it == fields.end()) { 
        throw std::out_of_range(
        "ObjectNode: no found by key: " + key
        );
    }
    return *it->second;
}

Node& ObjectNode::getPath(const std::string& path, Manager& manager) {
    // get position of first point
    size_t pos = path.find('.'); 
    
    // if path equal key
    if (pos == std::string::npos) return *fields[path]; 
    
    std::string first = path.substr(0, pos); // first key
    std::string rest = path.substr(pos + 1);   // rest path

    Node*& child = fields[first]; // get node
    // if Node equal nullptr
    if (!child) child = manager.create<ObjectNode>(); 

    return child->asObject().getPath(rest, manager);
}