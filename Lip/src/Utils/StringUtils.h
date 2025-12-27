#pragma once
#include <string>
#include <string_view>

namespace Utils {

//constexpr char RED[] = "\x1b[31m";
constexpr char RED[] = "\x1b[39m";
constexpr char GREEN[] = "\x1b[32m";
constexpr char BLUE[] = "\x1b[33m";
constexpr char DEFAULT[] = "\x1b[39m";

double toDouble(std::string_view s);
size_t toSizeType(std::string_view s);

std::string toString(double d);

}