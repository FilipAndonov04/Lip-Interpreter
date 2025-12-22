#include "CharUtils.h"

namespace StringUtils {

static bool isBetween(char ch, char beg, char end) {
    return ch >= beg && ch <= end;
}

bool isDigit(char ch) {
    return isBetween(ch, '0', '9');
}

bool isLowerLetter(char ch) {
    return isBetween(ch, 'a', 'z');
}

bool isUpperLetter(char ch) {
    return isBetween(ch, 'A', 'Z');
}

bool isLetter(char ch) {
    return isLowerLetter(ch) || isUpperLetter(ch);
}

bool isDigitOrLetter(char ch) {
    return isDigit(ch) || isLetter(ch);
}

bool isUnderscore(char ch) {
    return ch == '_';
}

bool isDash(char ch) {
    return ch == '-';
}

bool isLetterOrUnderscore(char ch) {
    return isLetter(ch) || isUnderscore(ch);
}

bool isDigitOrLetterOrUnderscore(char ch) {
    return isDigitOrLetter(ch) || isUnderscore(ch);
}

bool isWhitespace(char ch) {
    return ch == ' ' || ch == '\t' || ch == '\n';
}

bool isSign(char ch) {
    return isOpenParentheses(ch) || isCloseParentheses(ch) || isOpenBracket(ch) ||
        isCloseBracket(ch) || isEqualSign(ch) || isDolarSign(ch) || 
        isComma(ch) || isDot(ch);
}

bool isOpenParentheses(char ch) {
    return ch == '(';
}

bool isCloseParentheses(char ch) {
    return ch == ')';
}

bool isOpenBracket(char ch) {
    return ch == '[';
}

bool isCloseBracket(char ch) {
    return ch == ']';
}

bool isEqualSign(char ch) {
    return ch == '=';
}

bool isDolarSign(char ch) {
    return ch == '$';
}

bool isComma(char ch) {
    return ch == ',';
}

bool isDot(char ch) {
    return ch == '.';
}

}