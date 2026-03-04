#ifndef CONFIG_NODES_HPP
#define CONFIG_NODES_HPP

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

namespace Config {

enum class NodeType {
    ValueNode,
    ObjectNode,
    ArrayNode
};

class Node {
public:
    virtual ~Node() = default;
    virtual std::string serialize() = 0;
};

class ValueNode : public Node {
private:
    std::string value;  
public:
    std::string getValue(); 
};

class ObjectNode : public Node {
private:
    std::unordered_map<std::string, std::shared_ptr<Node>> fields;
public:
    std::unordered_map<std::string, std::shared_ptr<Node>> getValue(); 
};

class ArrayNode : public Node {
private:
    std::vector<std::shared_ptr<Node>> elements;
public:
    std::vector<std::shared_ptr<Node>> getValue(); 
};

}
#endif