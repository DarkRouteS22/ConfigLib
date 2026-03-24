#include "config/Node.h"

#include <algorithm>
#include <stdexcept>
#include <string>
#include <unordered_map>

using namespace Config;

Node& Node::operator[](const std::string& key) {
    asObject();
    return object_value_[key];
}

Node& Node::at(const std::string& key) {
    asObject();
    auto it = object_value_.find(key);
    if (it == object_value_.end()) 
        throw std::out_of_range("Node: out of rande in Object");
    return it->second;
}

Node& Node::path(const std::string& path) {
    Node* current = this;
    size_t start = 0;

    while (true) {
        size_t dot = path.find('.', start);
        std::string part = path.substr(start, dot - start);

        if (!part.empty() && std::all_of(part.begin(), part.end(), ::isdigit)) {
            size_t index = std::stoull(part);
            current = &((*current)[index]);
        } else {
            current = &((*current)[part]);
        }

        if (dot == std::string::npos) break;
        start = dot + 1;
    }

    return *current;
}

Node& Node::atPath(const std::string& path) {
    asObject();

    size_t pos = path.find(".");
    if (pos == std::string::npos) return object_value_.at(path);

    std::string first = path.substr(0, pos);
    std::string rest = path.substr(pos + 1);

    return object_value_.at(first).atPath(rest);
}