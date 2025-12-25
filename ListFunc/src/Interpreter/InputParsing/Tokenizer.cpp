#include "Tokenizer.h"

#include "Utils/CharUtils.h"

#include <stdexcept>
#include <sstream>

Tokenizer::Tokenizer(std::string_view line) 
    : line(line) {}

std::vector<std::string> Tokenizer::tokenize() const {
    size_t index = 0;

    std::vector<std::string> tokens;
    while (index < line.length()) {
        char symbol = line[index];
        if (Utils::isWhitespace(symbol)) {
            index++;
            continue;
        }

        if (Utils::isLetter(symbol)) {
            tokens.push_back(parseWord(index));
        } else if (Utils::isDigit(symbol) || Utils::isDash(symbol)) {
            tokens.push_back(parseNumber(index));
        } else if (Utils::isDoubleQuote(symbol)) {
            tokens.push_back(parseSign(index));
            tokens.push_back(parseString(index));
            tokens.push_back(parseSign(index));
        } else if (Utils::isSign(symbol)) {
            tokens.push_back(parseSign(index));
        } else {
            throw std::runtime_error(std::string("invalid symbol <") + symbol + "> in line");
        }
    }
    return tokens;
}

std::string Tokenizer::parseWord(size_t& index) const {
    std::string word(1, line[index++]);

    while (index < line.length() && Utils::isDigitOrLetterOrUnderscore(line[index])) {
        word.push_back(line[index++]);
    }

    return word;
}

std::string Tokenizer::parseNumber(size_t& index) const {
    std::string word(1, line[index++]);

    while (index < line.length() && Utils::isDigit(line[index])) {
        word.push_back(line[index++]);
    }

    if (index == line.length() || !Utils::isDot(line[index])) {
        return word;
    }

    word.push_back(line[index++]);
    while (index < line.length() && Utils::isDigit(line[index])) {
        word.push_back(line[index++]);
    }

    return word;
}

std::string Tokenizer::parseSign(size_t& index) const {
    return std::string(1, line[index++]);
}

std::string Tokenizer::parseString(size_t& index) const {
    std::stringstream ss;

    while (index < line.length() && !Utils::isDoubleQuote(line[index])) {
        ss << line[index++];
    }

    return ss.str();
}
