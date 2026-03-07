#ifndef CONFIG_MANAGER_HPP
#define CONFIG_MANAGER_HPP

#include "config/nodes.hpp"
#include <memory>
#include <vector>
#include <type_traits>

namespace Config {

class Manager {
private:
    std::vector<std::unique_ptr<Node>> storage;
public:
    Manager() = default;
    
    template<typename T>
    T* create() {
        static_assert(std::is_base_of_v<Config::Node, T>, "T must inherit Node");
        auto node = std::make_unique<T>();
        T* ptr = node.get();
        storage.push_back(std::move(node));
        return  ptr;
    }
};

}
#endif 


