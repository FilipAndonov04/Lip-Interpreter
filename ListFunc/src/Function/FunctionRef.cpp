#include "FunctionRef.h"
#include "Interpreter/VariableDatabase.h"

FunctionRef::FunctionRef(std::string name, size_t argCount, const VariableDatabase& database) 
    : name(std::move(name)), argCount(argCount), database(&database) {}

Function& FunctionRef::function() const {
    return database->getFunction(name, argCount);
}

Function& FunctionRef::operator*() const {
    return function();
}

Function* FunctionRef::operator->() const {
    return &function();
}

bool FunctionRef::isValid() const {
    return database->containsFunction(name, argCount);
}

FunctionRef::operator bool() const {
    return isValid();
}
