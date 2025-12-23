#pragma once

#include <string>
#include <string_view>
#include <vector>

class Tokenizer {
public:
	Tokenizer(std::string_view line);

	std::vector<std::string> tokenize() const;

private:
	std::string parseWord(size_t& index) const;
	std::string parseNumber(size_t& index) const;
	std::string parseSign(size_t& index) const;

	std::string_view line;
};