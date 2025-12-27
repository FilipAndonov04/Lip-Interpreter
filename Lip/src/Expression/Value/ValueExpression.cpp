#include "ValueExpression.h"
#include "Value/Value.h"

ValueExpression::ValueExpression(std::unique_ptr<Value>&& value) 
    : value(std::move(value)) {}

std::unique_ptr<Value> ValueExpression::evaluate() const {
    return value->cloneValue();
}

std::unique_ptr<Expression> ValueExpression::clone() const {
    return of(value->cloneValue());
}

std::string ValueExpression::toString() const {
    return value->toString();
}

std::unique_ptr<ValueExpression> ValueExpression::of(std::unique_ptr<Value>&& value) {
    return std::make_unique<ValueExpression>(std::move(value));
}
