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
};

class ValueNode : public Node {
public:
    enum class ValueType { // type of value
        Null,
        Int,
        String,
        Bool,
        Float
    };

    // set Velue functions
    void setInt(int64_t);
    void setFloat(double);
    void setBool(bool);
    void setString(std::string);
    void setNull();

    // get value type functions
    bool isInt() const;
    bool isFloat() const;
    bool isBool() const;
    bool isString() const;
    bool isNull() const;
    ValueType valueType() const;

    // get value functions with exception
    int64_t asInt() const;
    double asFloat() const;
    bool asBool() const;
    const std::string& asString() const;

    // get value or default functions
    int64_t tryAsInt(int64_t) const;
    double tryAsFloat(double) const;
    bool tryAsBool(bool) const;
    const std::string& tryAsString(const std::string&) const;

    // get Node type
    NodeType type() const override;
private:
    friend class Manager;
    ValueNode() = default;

    // Value data
    std::string strValue; 
    ValueType valType = ValueType::Null;

    union ValueData {
        int64_t i;
        double f;
        bool b;
    } data;
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