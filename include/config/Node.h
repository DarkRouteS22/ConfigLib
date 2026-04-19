#ifndef CONFIG_NODE_H_
#define CONFIG_NODE_H_

#include <optional>
#include <string>
#include <variant>
#include <vector>
#include <unordered_map>

namespace Config { 

// value data type
using value_data = std::variant<bool, double, int64_t, std::string>;

// type of Node
enum class NodeType {
    None,
    Object,
    Array,
    Value
};

class Node {
public:
    //? GENERAL

    //* create New Node with type None
    Node();

    //* create New Node with type from param
    Node(NodeType type);

    Node& operator=(Node node);
    
    //* if type equal Object or Array - return size of Object or Array, else - return 0
    size_t size() const;

    //? if type equal None - set type, else - exception
    //* set type to Object
    Node& asObject(); 

    //* set type to Array
    Node& asArray();

    //* set type to Value
    Node& asValue();

    //? check type
    bool isObject() const;
    bool isArray() const;
    bool isValue() const;
    bool isNone() const;

    NodeType nodeType() const;
    //? ARRAY

    //* return Node& or New Node& from index
    Node& operator[](size_t index);
 
    //* if exist - return Node& from index, else - exceprion 
    Node& at(size_t index);

    //* push back anr return New Node
    Node& add(Node node);
    
    //* iterator, if type not equal Array - exception 
    std::vector<Node>::iterator begin();
    std::vector<Node>::iterator end();
    
    //? OBJECT

    //* return Nobe& or New Node& from key
    Node& operator[](const std::string& key);

    //* if exist - return Node&, else - exception
    Node& at(const std::string& key);

    //* return Node& or New Node& from path
    //! if path has not Object Node or None Node - exception
    Node& path(const std::string& path);

    //* if path valid - return
    Node& atPath(const std::string& path);


    //? SET VALUE BLOCK
    //* if type not equal Value - exception

    Node& operator=(std::optional<value_data> value);
    Node& operator=(std::string value);
    Node& operator=(int64_t value);
    Node& operator=(double value);
    Node& operator=(bool value);
    Node& operator=(std::nullopt_t);
    
    Node& set(std::optional<value_data> value);
    Node& set(std::string value);
    Node& set(int64_t value);
    Node& set(double value);
    Node& set(bool value);
    Node& set(std::nullopt_t value);

    //? GET BLOCK
    //* if Value type not equal - exception

    std::optional<value_data> getValue() const;
    std::string getString() const;
    int64_t getInt() const;
    double getFloat() const;
    bool getBool() const;

    //? CHECK BLOCK
    bool isNull() const;
    bool isString() const;
    bool isInt() const;
    bool isFloat() const;
    bool isBool() const;

private:
    NodeType node_type_;

    std::optional<value_data> value_data_ = std::nullopt;
    std::vector<Node> array_data_;
    std::unordered_map<std::string, Node> object_data_;

};

}
#endif // CONFIG_NODE_H_