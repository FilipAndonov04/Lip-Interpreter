#include "StringLiteral.h"
#include "Value/String/String.h"

StringLiteral::StringLiteral(std::string string) 
    : string(string) {}

std::unique_ptr<Value> StringLiteral::evaluate() const {
    return String::of(string);
}

std::unique_ptr<Literal> StringLiteral::cloneLiteral() const {
    return of(string);
}

std::string StringLiteral::toString() const {
    return string;
}

const std::string& StringLiteral::getString() const {
    return string;
}

std::unique_ptr<StringLiteral> StringLiteral::of(std::string string) {
    return std::make_unique<StringLiteral>(std::move(string));
}
