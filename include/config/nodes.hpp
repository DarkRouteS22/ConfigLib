#ifndef CONFIG_NODES_HPP
#define CONFIG_NODES_HPP

#include <string>
#include <vector>
#include <unordered_map>
// #include <config/manager.hpp>

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
};

class ValueNode : public Node {
public:
    enum class ValueType {
        Int,
        String,
        Bool,
        Null,
        Float
    };

    const std::string& getValue() const;
    void set(const std::string&, ValueType);
    NodeType type() const override;
    ValueType valueType() const;
private:
    friend class Manager;
    ValueNode() = default;

private:
    std::string value; 
    ValueType vtype;
};

class ObjectNode : public Node {
public:
    std::unordered_map<std::string, Node*>& getValue();
    void add(const std::string&, Node*);
    void set(const std::unordered_map<std::string, Node*>&);
    bool contains(const std::string&) const;
    void remove(const std::string&);
    size_t size() const;
    NodeType type() const override;

private:
    friend class Manager;
    ObjectNode() = default;

private:
    std::unordered_map<std::string, Node*> fields;
};

class ArrayNode : public Node {
public:
    std::vector<Node*>& getValue(); 
    void add(Node*);
    void set(const std::vector<Node*>);
    size_t size() const;
    NodeType type() const override;
private:
    friend class Manager;
    ArrayNode() = default;

private:
    std::vector<Node*> elements;
};

}
#endif