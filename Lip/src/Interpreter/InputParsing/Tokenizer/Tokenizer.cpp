#include "Tokenizer.h"

#include "Utils/CharUtils.h"

#include <stdexcept>
#include <sstream>

Tokenizer::Tokenizer(std::string_view line) 
    : line(line) {}

std::vector<Token> Tokenizer::tokenize() const {
    std::vector<Token> tokens;
    size_t index = 0;

    while (index < line.length()) {
        char symbol = line[index];
        if (Utils::isWhitespace(symbol)) {
            index++;
            continue;
        }

        if (Utils::isLetter(symbol)) {
            tokens.push_back(parseWord(index));
        } else if (Utils::isDigit(symbol)) {
            tokens.push_back(parseNumber(index));
        } else if (Utils::isQuote(symbol)) {
            tokens.push_back(parseSign(index));
            tokens.push_back(parseText(index, tokens.back().type == TokenType::SingleQuote));
            tokens.push_back(parseSign(index));
        } else if (Utils::isSign(symbol)) {
            tokens.push_back(parseSign(index));
        } else {
            throw std::runtime_error(std::string("invalid symbol <") + symbol + "> in line");
        }
    }

    return tokens;
}

Token Tokenizer::parseWord(size_t& index) const {
    std::string word(1, line[index++]);

    while (index < line.length() && Utils::isDigitOrLetterOrUnderscore(line[index])) {
        word.push_back(line[index++]);
    }

    return Token{TokenType::Word, std::move(word)};
}

Token Tokenizer::parseNumber(size_t& index) const {
    TokenType type = TokenType::Number;
    std::string num(1, line[index++]);

    while (index < line.length() && Utils::isDigit(line[index])) {
        num.push_back(line[index++]);
    }

    if (index == line.length() || !Utils::isDot(line[index])) {
        return Token{type, std::move(num)};
    }

    num.push_back(line[index++]);
    while (index < line.length() && Utils::isDigit(line[index])) {
        num.push_back(line[index++]);
    }

    return Token{type, std::move(num)};
}

Token Tokenizer::parseText(size_t& index, bool isSingleQuoted) const {
    std::stringstream ss;
    auto isQuote = isSingleQuoted ? Utils::isSingleQuote : Utils::isDoubleQuote;

    while (index < line.length() && !isQuote(line[index])) {
        ss << line[index++];
    }

    return Token{TokenType::Text, ss.str()};
}

Token Tokenizer::parseSign(size_t& index) const {
    if (index == line.length()) {
        throw std::invalid_argument("a sign is missing");
    }

    TokenType type = [](char sign) {
        switch (sign) {
        case '(':
            return TokenType::OpenCircleBracket;
        case ')':
            return TokenType::CloseCircleBracket;
        case '[':
            return TokenType::OpenSquareBracket;
        case ']':
            return TokenType::CloseSquareBracket;
        case '{':
            return TokenType::OpenCurlyBracket;
        case '}':
            return TokenType::CloseCurlyBracket;
        case '=':
            return TokenType::Equal;
        case '$':
            return TokenType::Dolar;
        case ',':
            return TokenType::Comma;
        case '.':
            return TokenType::Dot;
        case '-':
            return TokenType::Dash;
        case '\'':
            return TokenType::SingleQuote;
        case '\"':
            return TokenType::DoubleQuote;
        default:
            throw std::invalid_argument("invalid sign");
        }
    }(line[index]);

    return Token{type, std::string(1, line[index++])};
}
