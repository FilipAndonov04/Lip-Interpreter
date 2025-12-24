#include "Function.h"
#include "Value/Value.h"

#include <stdexcept>
#include <string>

Function::Function(size_t argCount)
    : argCount(argCount) {}

std::unique_ptr<Value> Function::call(const std::vector<const Expression*>& args) const {
    if (args.size() != argCount) {
        throw std::runtime_error("function expects " + std::to_string(argCount) + 
                                 " arguments, but is called with " + std::to_string(args.size()));
    }

    return callImpl(args);
}

std::unique_ptr<Value> Function::operator()(const std::vector<const Expression*>& args) const {
    return call(args);
}

size_t Function::getArgCount() const {
    return argCount;
}