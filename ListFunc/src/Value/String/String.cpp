#include "String.h"

String::String(std::string string) 
    : string(std::move(string)) {}

ValueType String::type() const {
    return ValueType::String;
}

std::unique_ptr<Value> String::cloneValue() const {
    return of(string);
}

std::string String::toString() const {
    return '\"' + string + '\"';
}

const std::string& String::getString() const {
    return string;
}

void String::setString(std::string string) {
    this->string = std::move(string);
}

std::unique_ptr<String> String::of(std::string string) {
    return std::make_unique<String>(std::move(string));
}
