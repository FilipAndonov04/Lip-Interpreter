#include "FunctionRef.h"
#include "Interpreter/VariableSet/VariableSet.h"

#include <stdexcept>

FunctionRef::FunctionRef(std::string name, size_t argCount, const VariableSet& variableSet)
    : name(std::move(name)), argCount(argCount), variableSet(&variableSet) {}

const Function& FunctionRef::deref() const {
    return *ptr();
}

const Function* FunctionRef::ptr() const {
    auto func = variableSet->getFunction(name, argCount);
    if (!func) {
        throw std::runtime_error("there is not a function <" + name + "> that takes " +
                                 std::to_string(argCount) + " arguments");
    }

    return func;
}

const Function& FunctionRef::operator*() const {
    return deref();
}

const Function* FunctionRef::operator->() const {
    return ptr();
}

bool FunctionRef::isValid() const {
    return variableSet->containsFunction(name);
}

FunctionRef::operator bool() const {
    return isValid();
}

const std::string& FunctionRef::getName() const {
    return name;
}

size_t FunctionRef::getArgCount() const {
    return argCount;
}

const VariableSet& FunctionRef::getVariableSet() const {
    return *variableSet;
}
