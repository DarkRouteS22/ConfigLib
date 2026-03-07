#ifndef CONFIG_NODES_HPP
#define CONFIG_NODES_HPP

#include <string>
#include <vector>
#include <unordered_map>

namespace Config {
class ArrayNode;
class ValueNode;
class ObjectNode;

enum class NodeType {
    ValueNode,
    ObjectNode,
    ArrayNode
};

class Node {
public:
    virtual ~Node() = default;
    virtual NodeType type() const = 0;
    virtual std::string toString() = 0;
};

class ValueNode : public Node {
private:
    std::string value;  
public:
    ValueNode();
    std::string& getValue();
    void set(std::string&);

    NodeType type() const override;
    std::string toString() override;
};

class ObjectNode : public Node {
private:
    std::unordered_map<std::string, Node*> fields;
public:
    ObjectNode();

    std::unordered_map<std::string, Node*>& getValue();
    void add(const std::string&, Node*);
    void set(std::unordered_map<std::string, Node*>);
    
    size_t size() const;
    std::string toString() override;
    NodeType type() const override;

    // TODO: list() -> name : type
};

class ArrayNode : public Node {
private:
    std::vector<Node*> elements;
public:
    ArrayNode();

    std::vector<Node*> getValue(); 
    void add(Node*);
    void set(std::vector<Node*>);

    size_t size() const;
    NodeType type() const override;
    std::string toString() override;
};

}
#endif