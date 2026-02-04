#include "Keywords.h"

bool isKeyword(std::string_view word) {
    return word == KEYWORD_DEFINE_FUNCTION || word == KEYWORD_REDEFINE_FUNCTION ||
        word == KEYWORD_UNDEFINE_FUNCTION || word == KEYWORD_CREATE_VARIABLE ||
        word == KEYWORD_CREATE_CONST_VARIABLE || word == KEYWORD_REMOVE_VARIABLE;
}