#include "Variable.h"

std::unique_ptr<Variable> Variable::evaluate() const {
    return cloneVariable();
}

ExpressionType Variable::type() const {
    return ExpressionType::Variable;
}

std::unique_ptr<Expression> Variable::cloneExpression() const {
    return cloneVariable();
}
