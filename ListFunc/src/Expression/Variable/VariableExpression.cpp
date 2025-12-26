#include "VariableExpression.h"
#include "Value/Value.h"

VariableExpression::VariableExpression(const Value* variable) 
    : variable(variable) {}

std::unique_ptr<Value> VariableExpression::evaluate() const {
    return variable->cloneValue();
}

std::unique_ptr<Expression> VariableExpression::clone() const {
    return of(variable);
}

std::string VariableExpression::toString() const {
    return "{var}";
}

const Value* VariableExpression::getVariable() const {
    return variable;
}

std::unique_ptr<VariableExpression> VariableExpression::of(const Value* variable) {
    return std::make_unique<VariableExpression>(variable);
}
