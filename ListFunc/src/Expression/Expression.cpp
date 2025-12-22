#include "Expression.h"
#include "Variable/Variable.h"

std::unique_ptr<Variable> Expression::evaluate(std::unique_ptr<Expression>&& expression) {
    if (auto var = dynamic_cast<Variable*>(expression.get())) {
        expression.release();
        return std::unique_ptr<Variable>(var);
    }
    return expression->evaluate();
}