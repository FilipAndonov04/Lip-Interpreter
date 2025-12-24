#include "Literal.h"

std::unique_ptr<Expression> Literal::cloneExpression() const {
    return cloneLiteral();
}
