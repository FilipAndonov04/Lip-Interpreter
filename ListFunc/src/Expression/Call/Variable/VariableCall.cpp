#include "VariableCall.h"
#include "Value/Value.h"

VariableCall::VariableCall(const Value* variable) 
    : variable(variable) {}

std::unique_ptr<Value> VariableCall::evaluate() const {
    return variable->cloneValue();
}

std::unique_ptr<Expression> VariableCall::cloneExpression() const {
    return of(variable);
}

std::string VariableCall::toString() const {
    return "{var}";
}

const Value* VariableCall::getVariable() const {
    return variable;
}

std::unique_ptr<VariableCall> VariableCall::of(const Value* variable) {
    return std::make_unique<VariableCall>(variable);
}
