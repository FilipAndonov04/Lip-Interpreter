#include "Interpreter.h"
#include "Interpreter/InputParsing/Tokenizer/Tokenizer.h"
#include "Interpreter/InputParsing/Factory/ObjectFactory.h"
#include "Expression/Expression.h"
#include "Value/Value.h"

#include "Utils/CharUtils.h"
#include "Utils/StringUtils.h"

#include <iostream>

void Interpreter::interpret(std::string_view line) {
    try {
        Tokenizer tokenizer(line);
        auto tokens = tokenizer.tokenize();

        if (tokens.empty()) {
            return;
        }

        if (tokens[0].payload == "def") {
            handleFunctionDefinition(std::move(tokens));
        } else {
            handleExpressionEvaluation(std::move(tokens));
        }
    } catch (const std::exception& e) {
        std::cout << "[ERROR] " << e.what() << '\n';
    }
}

const Environment& Interpreter::getCurrentEnvironment() const {
    return *currentEnvironment;
}

Environment& Interpreter::getCurrentEnvironment() {
    return *currentEnvironment;
}

void Interpreter::setCurrentEnvironment(std::unique_ptr<Environment>&& environment) {
    environment->setPreviousEnvironment(std::move(currentEnvironment));
    currentEnvironment = std::move(environment);
}

void Interpreter::handleFunctionDefinition(std::vector<Token>&& tokens) {
    if (tokens.size() < 6) {
        throw std::invalid_argument("invalid function definition");
    }

    std::string name = std::move(tokens[1].payload);
    size_t argCount = Utils::toSizeType(tokens[3].payload);

    std::unique_ptr<Environment> nextEnvironment = std::make_unique<Environment>(*currentEnvironment);

    ObjectFactory factory(std::move(tokens), *nextEnvironment, 6);
    auto func = factory.createFunction(name, argCount);

    nextEnvironment->setPreviousEnvironment(std::move(currentEnvironment));
    currentEnvironment = std::move(nextEnvironment);

    std::cout << "defining function <" << name << '(' << argCount << ")>\n";
}

void Interpreter::handleExpressionEvaluation(std::vector<Token>&& tokens) const {
    ObjectFactory factory(std::move(tokens), *currentEnvironment);

    auto expr = factory.createExpression();
    auto res = expr->evaluate();

    std::cout << res->toString() << " <- " << expr->toString() << '\n';
}
