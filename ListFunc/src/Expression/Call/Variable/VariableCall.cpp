#include "VariableCall.h"

VariableCall::VariableCall(VariableRef variableRef)
    : variableRef(std::move(variableRef)) {}

std::unique_ptr<Value> VariableCall::evaluate() const {
    return variableRef->cloneVariable();
}

ExpressionType VariableCall::type() const {
    return ExpressionType::VariableCall;
}

std::unique_ptr<Expression> VariableCall::cloneExpression() const {
    return std::make_unique<VariableCall>(variableRef);
}

std::string VariableCall::toString() const {
    return '{' + variableRef.getName() + '}';
}
