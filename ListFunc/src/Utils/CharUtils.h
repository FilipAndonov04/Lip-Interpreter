#pragma once

namespace Utils {

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

bool isOpenCircleBracket(char ch);
bool isCloseCircleBracket(char ch);
bool isOpenSquareBracket(char ch);
bool isCloseSquareBracket(char ch);
bool isOpenCurlyBracket(char ch);
bool isCloseCurlyBracket(char ch);

bool isEqualSign(char ch);
bool isDolarSign(char ch);
bool isComma(char ch);
bool isDot(char ch);

bool isSingleQuote(char ch);
bool isDoubleQuote(char ch);

int toInt(char ch);

}