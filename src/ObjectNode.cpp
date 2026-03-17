#include <config/Node.h>
#include <stdexcept>

using namespace Config;

Node& Node::operator[](const std::string& key) {
    asObject();
    return obj[key];
}

Node& Node::at(const std::string& key) {
    asObject();
    auto it = obj.find(key);
    if (it == obj.end()) 
        throw std::out_of_range("Node: out of rande in Object");
    return it->second;
}

Node& Node::path(const std::string& path) {
    asObject();
    size_t pos = path.find('.');
    if (pos == std::string::npos) return obj[path];

    std::string first = path.substr(0, pos);
    std::string rest = path.substr(pos + 1);

    return obj[first].path(rest);
}

Node& Node::atPath(const std::string& path) {
    asObject();

    size_t pos = path.find(".");
    if (pos == std::string::npos) return obj.at(path);

    std::string first = path.substr(0, pos);
    std::string rest = path.substr(pos + 1);

    return obj.at(first).atPath(rest);
}