#include "Variable.h"

std::unique_ptr<Variable> Variable::evaluate() const {
    return cloneVariable();
}

std::unique_ptr<Expression> Variable::cloneExpression() const {
    return cloneVariable();
}
