#include "StringUtils.h"
#include "Utils/CharUtils.h"

#include <stdexcept>

namespace Utils {

double toDouble(std::string_view s) {
    if (s.empty()) {
        throw std::invalid_argument("empty string");
    }

    if (isDash(s.front())) {
        return -toDouble(s.substr(1));
    }

    size_t index = 0;
    double num = 0.0;
    while (index < s.length() && isDigit(s[index])) {
        num = num * 10 + toInt(s[index++]);
    }

    if (index == s.length()) {
        return num;
    } else if (!isDot(s[index])) {
        throw std::invalid_argument("invalid character in number");
    }

    index++;
    double multiplier = 1.0;
    while (index < s.length() && isDigit(s[index])) {
        multiplier *= 0.1;
        num += toInt(s[index++]) * multiplier;
    }

    if (index != s.length()) {
        throw std::invalid_argument("invalid character in number");
    }
    return num;
}

size_t toSizeType(std::string_view s) {
    if (s.empty()) {
        throw std::invalid_argument("empty string");
    }

    size_t index = 0;
    size_t num = 0;
    while (index < s.length() && isDigit(s[index])) {
        num = num * 10 + toInt(s[index++]);
    }

    if (index != s.length()) {
        throw std::invalid_argument("invalid character in non-negative integer");
    }

    return num;
}

std::string toString(double d) {
    constexpr size_t DIGITS_AFTER_DECIMAL_POINT = 6;
    constexpr size_t DIGITS_TO_ALWAYS_TRIM = 3;
    static_assert(DIGITS_TO_ALWAYS_TRIM <= DIGITS_AFTER_DECIMAL_POINT,
                  "cannot trim more digits than there are");

    std::string s = std::to_string(d);
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

}