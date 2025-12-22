#pragma once

namespace StringUtils {

bool isDigit(char ch);
bool isLowerLetter(char ch);
bool isUpperLetter(char ch);
bool isLetter(char ch);
bool isDigitOrLetter(char ch);

bool isUnderscore(char ch);
bool isDash(char ch);

bool isLetterOrUnderscore(char ch);
bool isDigitOrLetterOrUnderscore(char ch);

bool isWhitespace(char ch);

bool isSign(char ch);

bool isOpenParentheses(char ch);
bool isCloseParentheses(char ch);
bool isOpenBracket(char ch);
bool isCloseBracket(char ch);

bool isEqualSign(char ch);
bool isDolarSign(char ch);
bool isComma(char ch);
bool isDot(char ch);

}