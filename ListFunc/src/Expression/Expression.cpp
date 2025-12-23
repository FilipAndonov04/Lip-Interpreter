#include "Expression.h"
#include "Variable/Variable.h"

std::unique_ptr<Variable> Expression::evaluate(std::unique_ptr<Expression>&& expression) {
    if (isVariable(expression->type())) {
        auto var = static_cast<Variable*>(expression.release());
        return std::unique_ptr<Variable>(var);
    }
    return expression->evaluate();
}