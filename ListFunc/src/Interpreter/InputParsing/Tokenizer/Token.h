#pragma once
#include "Interpreter/InputParsing/Tokenizer/TokenType.h"

#include <string>

struct Token {
	TokenType type;
	std::string payload;
};