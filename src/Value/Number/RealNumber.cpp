#include "RealNumber.h"

#include "Utils/StringUtils.h"

RealNumber::RealNumber(double value)
    : value(value) {}

ValueType RealNumber::type() const {
    return ValueType::Number;
}

std::unique_ptr<Value> RealNumber::cloneValue() const {
    return of(value);
}

std::string RealNumber::toString() const {
    return Utils::toString(value);
}

double RealNumber::getValue() const {
    return value;
}

void RealNumber::setValue(double value) {
    this->value = value;
}

std::unique_ptr<RealNumber> RealNumber::of(double value) {
    return std::make_unique<RealNumber>(value);
}
