#pragma once
#include "Interpreter/InputParsing/Tokenizer/Token.h"

#include <string_view>
#include <vector>

class Tokenizer {
public:
	Tokenizer(std::string_view line);

	std::vector<Token> tokenize() const;

private:
	Token parseWord(size_t& index) const;
	Token parseNumber(size_t& index) const;
	Token parseText(size_t& index, bool isSingleQuoted) const;
	Token parseSign(size_t& index) const;

	std::string_view line;
};