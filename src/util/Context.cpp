#include "config/Context.h"

#include "config/Node.h"

using namespace Config;

Node& Context::parent() {
    return *parent_;
}