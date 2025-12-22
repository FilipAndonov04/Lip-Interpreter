#include "RealNumber.h"

RealNumber::RealNumber(double value)
    : value(value) {}

std::unique_ptr<Number> RealNumber::cloneNumber() const {
    return of(value);
}

std::string RealNumber::toString() const {
    constexpr size_t DIGITS_AFTER_DECIMAL_POINT = 6;
    constexpr size_t DIGITS_TO_ALWAYS_TRIM = 3;
    static_assert(DIGITS_TO_ALWAYS_TRIM <= DIGITS_AFTER_DECIMAL_POINT,
                  "cannot trim more digits than there are");

    std::string s = std::to_string(value);
    s.erase(s.end() - DIGITS_TO_ALWAYS_TRIM, s.end());

    size_t leftToTrim = DIGITS_AFTER_DECIMAL_POINT - DIGITS_TO_ALWAYS_TRIM;
    while (leftToTrim-- > 0 && s.back() == '0') {
        s.pop_back();
    }
    if (s.back() == '.') {
        s.pop_back();
    }

    return s;
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
