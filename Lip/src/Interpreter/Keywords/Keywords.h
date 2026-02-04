#pragma once

#include <string_view>

constexpr const char KEYWORD_DEFINE_FUNCTION[] = "def";
constexpr const char KEYWORD_REDEFINE_FUNCTION[] = "redef";
constexpr const char KEYWORD_UNDEFINE_FUNCTION[] = "undef";

constexpr const char KEYWORD_CREATE_VARIABLE[] = "let";
constexpr const char KEYWORD_CREATE_CONST_VARIABLE[] = "const";
constexpr const char KEYWORD_REMOVE_VARIABLE[] = "rm";

bool isKeyword(std::string_view word);