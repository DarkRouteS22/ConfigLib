#ifndef CONFIG_NODE_H_
#define CONFIG_NODE_H_

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
    Node(NodeType type);

    NodeType nodeType() const;
    size_t size() const;

    bool isObject() const;
    bool isArray() const;
    bool isValue() const;
    bool isNone() const;

    Node& asObject();
    Node& asArray();
    Node& asValue();

    // array
    Node& operator[](size_t index);
    Node& at(size_t index);
    Node& add();
    
    std::vector<Node>::iterator begin();
    std::vector<Node>::iterator end();
    
    // object
    Node& operator[](const std::string& key);
    Node& at(const std::string& key);
    Node& path(const std::string& key);
    Node& atPath(const std::string& key);

    // value
    ValueType valueType() const;

    void operator=(int64_t value);
    void operator=(int value);
    void operator=(bool value);
    void operator=(double value);
    void operator=(const std::string& value);
    void operator=(const char* value);

    Node& set(int64_t value);
    Node& set(bool value);
    Node& set(double value);
    Node& set(const std::string& value);
    Node& set(const char* value);

    std::string asString() const;
    int64_t asInt() const;
    double asFloat() const;
    bool asBool() const;

    Node& toString();
    Node& toInt();
    Node& toFloat();
    Node& toBool();

    bool isNull() const;
    bool isString() const;
    bool isInt() const;
    bool isFloat() const;
    bool isBool() const;
    
    int64_t tryAsInt(int64_t def) const;
    double tryAsFloat(double def) const;
    bool tryAsBool(bool def) const;
    const std::string& tryAsString(const std::string& def) const;

private:
    NodeType node_type_ = NodeType::None;

    ValueType value_type_ = ValueType::Null;
    union {
        bool bool_value_;
        double float_value_;
        int64_t int_value_;
    } value_data_;
    std::string string_value_;

    std::vector<Node> array_value_;

    std::unordered_map<std::string, Node> object_value_;
};

}
#endif // CONFIG_NODE_H_