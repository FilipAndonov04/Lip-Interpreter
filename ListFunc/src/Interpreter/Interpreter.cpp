#include "Interpreter.h"
#include "Interpreter/InputParsing/Tokenizer.h"
#include "Interpreter/InputParsing/ObjectFactory.h"
#include "Expression/Expression.h"

#include "StringUtils/CharUtils.h"
#include "StringUtils/StringUtils.h"

#include <iostream>

Interpreter::Interpreter(VariableSet&& variableSet) 
    : variableSet(std::move(variableSet)) {}

void Interpreter::interpret(std::string_view line) {
    try {
        Tokenizer tokenizer(line);
        auto tokens = tokenizer.tokenize();

        if (tokens.empty()) {
            return;
        }

        if (tokens[0] == "def") {
            handleFunctionDefinition(std::move(tokens));
        } else {
            handleExpressionEvaluation(std::move(tokens));
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

void Interpreter::handleFunctionDefinition(std::vector<std::string>&& tokens) {
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
}

void Interpreter::handleExpressionEvaluation(std::vector<std::string>&& tokens) const {
    ObjectFactory factory(std::move(tokens), variableSet);

    auto expr = factory.createExpression();
    auto res = expr->evaluate();

    std::cout << expr->toString() << " " << res->toString() << '\n';
}
