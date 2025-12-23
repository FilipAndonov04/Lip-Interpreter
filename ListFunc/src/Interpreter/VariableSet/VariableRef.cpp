#include "VariableRef.h"
#include "Interpreter/VariableSet/VariableSet.h"

#include <stdexcept>

VariableRef::VariableRef(std::string name, const VariableSet& variableSet)
    : name(std::move(name)), variableSet(&variableSet) {}

const Variable& VariableRef::deref() const {
    return *ptr();
}

const Variable* VariableRef::ptr() const {
    auto var = variableSet->getVariable(name);
    if (!var) {
        throw std::runtime_error("there is not a variable named <" + name + ">");
    }

    return var;
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
