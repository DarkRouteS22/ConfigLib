#ifndef CONFIG_CONTEXT_H_
#define CONFIG_CONTEXT_H_

namespace Config {
class Node;

enum class Wait {
    Value,          
// * Ожидание Значения: { [ str num bool 
    Object,         
// * Ожидание Значени объекта: ключ или }
    Array,          
// * Ожидание Значений объекта: ждём значение или ]
    AfterKey,       
// * Ожидание После ключа: ждём :
    AfterOValue, 
// * Ожидание После Значения Объекта: ждём , или }
    AfterAValue,    
// * Ожидание После Значения Массива: ждём , или ]
    None
};

struct Context {
    Wait wait;
    Node& parent();
private:
    Node* parent_;
};
}
#endif // CONFIG_CONTEXT_H_