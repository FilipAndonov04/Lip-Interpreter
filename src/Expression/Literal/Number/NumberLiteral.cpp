#include "NumberLiteral.h"
#include "Value/Number/RealNumber.h"

#include "Utils/StringUtils.h"

NumberLiteral::NumberLiteral(double value) 
    : value(value) {}

std::unique_ptr<Value> NumberLiteral::evaluate() const {
    return RealNumber::of(value);
}

std::unique_ptr<Expression> NumberLiteral::clone() const {
    return of(value);
}

std::string NumberLiteral::toString() const {
    return Utils::toString(value);
}

double NumberLiteral::getValue() const {
    return value;
}

std::unique_ptr<NumberLiteral> NumberLiteral::of(double value) {
    return std::make_unique<NumberLiteral>(value);
}
