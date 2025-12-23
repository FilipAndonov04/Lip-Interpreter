#include "VariableRef.h"
#include "Interpreter/VariableSet/VariableSet.h"

#include <stdexcept>

VariableRef::VariableRef(std::string name, const VariableSet& variableSet) {}

const Variable& VariableRef::deref() const {
    auto ptrv = ptr();
    if (!ptrv) {
        throw std::runtime_error("there is not a variable named <" + name + ">");
    }

    return *ptrv;
}

const Variable* VariableRef::ptr() const {
    return variableSet->getVariable(name);
}

const Variable& VariableRef::operator*() const {
    return deref();
}

const Variable* VariableRef::operator->() const {
    return ptr();
}

bool VariableRef::isValid() const {
    return variableSet->containsVariable(name);
}

VariableRef::operator bool() const {
    return isValid();
}

const std::string& VariableRef::getName() const {
    return name;
}

const VariableSet& VariableRef::getVariableSet() const {
    return *variableSet;
}
