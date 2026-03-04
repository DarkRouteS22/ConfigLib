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
    virtual NodeType type() const = 0;
};

class ValueNode : public Node {
private:
    std::string value;  
public:
    std::string getValue(); 
    NodeType type() const override { return NodeType::ValueNode; };
};

class ObjectNode : public Node {
private:
    std::unordered_map<std::string, std::shared_ptr<Node>> fields;
public:
    std::unordered_map<std::string, std::shared_ptr<Node>> getValue(); 
    NodeType type() const override { return NodeType::ObjectNode; };
};

class ArrayNode : public Node {
private:
    std::vector<std::shared_ptr<Node>> elements;
public:
    std::vector<std::shared_ptr<Node>> getValue(); 
    NodeType type() const override { return NodeType::ArrayNode; };
};

}
#endif