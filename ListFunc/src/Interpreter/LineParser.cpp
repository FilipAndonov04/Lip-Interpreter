#include "LineParser.h"
#include "StringUtils/CharUtils.h"

#include <stdexcept>

LineParser::LineParser(std::string_view line) 
    : line(line) {}

std::vector<std::string> LineParser::tokenize() {
    std::vector<std::string> tokens;
    while (index < line.length()) {
        char symbol = line[index];
        if (StringUtils::isWhitespace(symbol)) {
            index++;
            continue;
        }

        if (StringUtils::isLetter(symbol)) {
            tokens.push_back(parseWord());
        } else if (StringUtils::isDigit(symbol) || StringUtils::isDash(symbol)) {
            tokens.push_back(parseNumber());
        } else if (StringUtils::isSign(symbol)) {
            tokens.push_back(parseSign());
        } else {
            throw std::runtime_error(std::string("invalid symbol <") + symbol + "> in line");
        }
    }
    return tokens;
}

std::string LineParser::parseWord() {
    std::string word(1, line[index++]);

    while (index < line.length() && StringUtils::isDigitOrLetterOrUnderscore(line[index])) {
        word.push_back(line[index++]);
    }

    return word;
}

std::string LineParser::parseNumber() {
    std::string word(1, line[index++]);

    while (index < line.length() && StringUtils::isDigit(line[index])) {
        word.push_back(line[index++]);
    }

    if (!StringUtils::isDot(line[index])) {
        return word;
    }

    word.push_back(line[index++]);
    while (index < line.length() && StringUtils::isDigit(line[index])) {
        word.push_back(line[index++]);
    }

    return word;
}

std::string LineParser::parseSign() {
    return std::string(1, line[index++]);
}
