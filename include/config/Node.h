#ifndef CONFIG_NODE_H
#define CONFIG_NODE_H

#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>

namespace Config {

enum class NodeType {
    None,
    Value,
    Object,
    Array
};

enum class ValueType {
    Null,
    String,
    Int,
    Float,
    Bool
};

class Node {
public:
    // general
    Node() = default;
    Node(NodeType);

    NodeType type() const;
    size_t size() const;

    bool isObject() const;
    bool isArray() const;
    bool isValue() const;
    bool none() const;

    Node& asObject();
    Node& asArray();
    Node& asValue();

    // array
    Node& operator[](size_t);
    Node& at(size_t);
    Node& add();
    
    __gnu_cxx::__normal_iterator<Config::Node *, std::vector<Config::Node, std::allocator<Config::Node>>> begin();
    __gnu_cxx::__normal_iterator<Config::Node *, std::vector<Config::Node, std::allocator<Config::Node>>> end();

    // object
    Node& operator[](const std::string&);
    Node& at(const std::string&);
    Node& path(const std::string&);
    Node& atPath(const std::string&);

    // value
    ValueType valueType() const;

    Node& operator=(int);
    Node& operator=(bool);
    Node& operator=(double);
    Node& operator=(const std::string&);
    Node& operator=(const char*);

    Node& set(int);
    Node& set(bool);
    Node& set(double);
    Node& set(const std::string&);
    Node& set(const char*);

    std::string asString();
    int64_t asInt();
    double asFloat();
    bool asBool();

    bool isNull() const;
    bool isString() const;
    bool isInt() const;
    bool isFloat() const;
    bool isBool() const;
    
    int64_t tryAsInt(int64_t) const;
    double tryAsFloat(double) const;
    bool tryAsBool(bool) const;
    const std::string& tryAsString(const std::string&) const;

private:
    NodeType nodeType = NodeType::None;
    ValueType valType = ValueType::Null;
    union {
        bool b;
        double f;
        int64_t i;
    } data;
    std::string s;
    std::vector<Node> arr;
    std::unordered_map<std::string, Node> obj;
};

}
#endif