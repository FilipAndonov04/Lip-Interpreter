#include "Function.h"
#include "Value/Value.h"

#include <stdexcept>
#include <string>

std::unique_ptr<Value> Function::call(const std::vector<const Expression*>& args) const {
    return callImpl(args);
}

std::unique_ptr<Value> Function::operator()(const std::vector<const Expression*>& args) const {
    return call(args);
}