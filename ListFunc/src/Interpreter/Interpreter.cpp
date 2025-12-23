#include "Interpreter.h"

#include "StringUtils/CharUtils.h"
#include "StringUtils/StringUtils.h"

#include <iostream>

Interpreter::Interpreter(VariableSet&& variableSet) 
    : variableSet(std::move(variableSet)) {}

void Interpreter::interpret(std::string_view line) {
    try {
        LineParser parser(line);
        auto tokens = parser.tokenize();

        if (tokens.empty()) {
            return;
        }

        if (tokens[0] == "def") {
            if (tokens.size() < 6) {
                throw std::invalid_argument("invalid function definition");
            }

            std::string funcName = std::move(tokens[1]);
            size_t argCount = StringUtils::toSizeType(tokens[3]);

            ObjectFactory factory(std::move(tokens), variableSet, 6);

            auto func = factory.createFunction(argCount);
            variableSet.removeFunction(funcName, func->getArgCount());
            variableSet.add(funcName, std::move(func));

            std::cout << "defining function <" << funcName << '(' << argCount << ")>\n";
        } else {
            ObjectFactory factory(std::move(tokens), variableSet);

            auto expr = factory.createExpression();
            auto res = Expression::evaluate(std::move(expr));

            std::cout << expr->toString() << " " << res->toString() << '\n';
        }
    } catch (const std::exception& e) {
        std::cout << "[ERROR] " << e.what() << '\n';
    }
}

const VariableSet& Interpreter::getVariableSet() const {
    return variableSet;
}

VariableSet& Interpreter::getVariableSet() {
    return variableSet;
}
