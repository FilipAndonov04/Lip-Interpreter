#pragma once

#include <string>
#include <string_view>
#include <vector>

class LineParser {
public:
	LineParser(std::string_view line);

	std::vector<std::string> tokenize();

private:
	std::string parseWord();
	std::string parseNumber();
	std::string parseSign();

	std::string_view line;
	size_t index = 0;
};