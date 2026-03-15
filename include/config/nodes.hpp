#ifndef CONFIG_NODES_HPP
#define CONFIG_NODES_HPP

#include <config/manager.hpp>
#include <string>
#include <vector>
#include <unordered_map>

namespace Config {
class ArrayNode;
class ValueNode;
class ObjectNode;
class Manager;



enum class NodeType {
    ValueNode,
    ObjectNode,
    ArrayNode
};

class Node {
public:
    virtual ~Node() = default;
    virtual NodeType type() const = 0;

    Node& operator[](const std::string&);
    Node& operator[](int);

    ObjectNode& asObject();
    const ObjectNode& asObject() const;

    ValueNode& asValue();
    const ValueNode& asValue() const;

    ArrayNode& asArray();
    const ArrayNode& asArray() const;

    ObjectNode* tryAsObject();
    ValueNode* tryAsValue();
    ArrayNode* tryAsArray();
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
    // get ptr to Node
    // get child value by key with throw
    Node& operator[](const std::string&);  

    // get child value by key
    Node& at(const std::string&);      

    // get nested value by path with throw
    Node& getPath(const std::string&, Manager&);


    size_t size() const;
    NodeType type() const override;

private:
    friend class Manager;
    ObjectNode() = default;

    std::unordered_map<std::string, Node*> fields;
};

class ArrayNode : public Node {
public:
    Node& operator[](unsigned int);
    Node& at(unsigned int);
    
    Node& add(Node&);
    template<typename T>
    T& add(Manager& manager) {
        T* ptr = manager.create<T>();
        elements.push_back(ptr);
        return *ptr;
    }

    size_t size() const;
    NodeType type() const override;
private:
    friend class Manager;
    ArrayNode() = default;

    std::vector<Node*> elements;
};

}
#endif