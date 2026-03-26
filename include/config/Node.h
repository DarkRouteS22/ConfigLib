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
static std::string ToString(NodeType t)
{
    switch (t)
    {
        case NodeType::None:   return "none";
        case NodeType::Value:   return "value";
        case NodeType::Object: return "obj";
        default: return "arr";
    }
}

    // general
    Node() = default;
    Node(NodeType type);
    Node(const Node& node);
    Node(Node&& node);
    Node& operator=(const Node&);
    Node& operator=(Node&&);


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

    void operator=(long value);
    void operator=(bool value);
    void operator=(double value);
    void operator=(const std::string& value);
    void operator=(const char* value);
    void operator=(std::nullptr_t);

    Node& setInt(long value);
    Node& setBool(bool value);
    Node& setFloat(double value);
    Node& setString(const std::string& value);
    Node& setString(const char* value);
    Node& setNull();

    std::string asString() const;
    long asInt() const;
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
    
    int64_t tryAsInt(long def) const;
    double tryAsFloat(double def) const;
    bool tryAsBool(bool def) const;
    const std::string& tryAsString(const std::string& def) const;

private:
    NodeType node_type_ = NodeType::None;

    ValueType value_type_ = ValueType::Null;
    union {
        bool bool_value_;
        double float_value_;
        long int_value_;
    } value_data_;
    std::string string_value_;

    std::vector<Node> array_value_;

    std::unordered_map<std::string, Node> object_value_;
};

}
#endif // CONFIG_NODE_H_