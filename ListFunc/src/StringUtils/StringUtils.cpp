#include "StringUtils.h"
#include "StringUtils/CharUtils.h"

#include <stdexcept>

namespace StringUtils {

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
        throw std::invalid_argument("invalid character in number");
    }
    return num;
}

}