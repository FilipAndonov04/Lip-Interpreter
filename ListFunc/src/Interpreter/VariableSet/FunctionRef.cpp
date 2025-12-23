#include "FunctionRef.h"

FunctionRef::FunctionRef(std::string name, size_t argCount, const VariableSet& variableSet)
    : name(std::move(name)), argCount(argCount), variableSet(&variableSet) {}

Function& FunctionRef::function() const {
    return variableSet->getFunction(name, argCount);
}

Function& FunctionRef::operator*() const {
    return function();
}

Function* FunctionRef::operator->() const {
    return &function();
}

bool FunctionRef::isValid() const {
    return variableSet->containsFunction(name, argCount);
}

FunctionRef::operator bool() const {
    return isValid();
}
