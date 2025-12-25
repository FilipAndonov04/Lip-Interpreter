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

        if (tokens[0].payload == KEYWORD_DEFINE_FUNCTION) {
            defineFunction(std::move(tokens));
        } else if (tokens[0].payload == KEYWORD_REDEFINE_FUNCTION) {
            redefineFunction(std::move(tokens));
        } else if (tokens[0].payload == KEYWORD_UNDEFINE_FUNCTION) {
            undefineFunction(std::move(tokens));
        } else {
            evaluateExpression(std::move(tokens));
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

void Interpreter::defineFunction(std::vector<Token>&& tokens) {
    if (!isValidFunctionDefinition(tokens)) {
        throw std::invalid_argument(std::string("defining function must be in the following format: ") +
                                    KEYWORD_DEFINE_FUNCTION + " <func_name>(<num_args>) = <func_body>");
    }

    std::string funcName = std::move(tokens[1].payload);
    size_t argCount = Utils::toSizeType(tokens[3].payload);
    if (currentEnvironment->containsFunction(funcName, argCount)) {
        throw std::invalid_argument("function <" + funcName + "(" + 
                                    std::to_string(argCount) + ")> is already defined");
    }

    std::unique_ptr<Environment> nextEnvironment = std::make_unique<Environment>(*currentEnvironment);

    ObjectFactory factory(std::move(tokens), *nextEnvironment, 6);
    auto func = factory.createFunction(funcName, argCount);

    nextEnvironment->setPreviousEnvironment(std::move(currentEnvironment));
    currentEnvironment = std::move(nextEnvironment);

    std::cout << "defining function <" << funcName << '(' << argCount << ")>\n";
}

void Interpreter::redefineFunction(std::vector<Token>&& tokens) {
    if (!isValidFunctionRedefinition(tokens)) {
        throw std::invalid_argument(std::string("redefining function must be in the following format: ") +
                                    KEYWORD_REDEFINE_FUNCTION + " <func_name>(<num_args>) = <func_body>");
    }

    std::string funcName = std::move(tokens[1].payload);
    size_t argCount = Utils::toSizeType(tokens[3].payload);
    if (!currentEnvironment->containsFunction(funcName, argCount)) {
        throw std::invalid_argument("function <" + funcName +
                                    "(" + std::to_string(argCount) + ")> is not defined");
    }

    std::unique_ptr<Environment> nextEnvironment = std::make_unique<Environment>(*currentEnvironment);
    if (!nextEnvironment->removeFunction(funcName, argCount)) {
        throw std::invalid_argument("function redefining failed");
    }

    ObjectFactory factory(std::move(tokens), *nextEnvironment, 6);
    auto func = factory.createFunction(funcName, argCount);

    nextEnvironment->setPreviousEnvironment(std::move(currentEnvironment));
    currentEnvironment = std::move(nextEnvironment);

    std::cout << "redefining function <" << funcName << '(' << argCount << ")>\n";
}

void Interpreter::undefineFunction(std::vector<Token>&& tokens) {
    if (!isValidFunctionUndefinition(tokens)) {
        throw std::invalid_argument(std::string("undefining function must be in the following format: ") +
                                    KEYWORD_UNDEFINE_FUNCTION + " <func_name>(<num_args>)");
    }

    std::string funcName = std::move(tokens[1].payload);
    size_t argCount = Utils::toSizeType(tokens[3].payload);
    if (!currentEnvironment->containsFunction(funcName, argCount)) {
        throw std::invalid_argument("function <" + funcName +
                                    "(" + std::to_string(argCount) + ")> was already not defined");
    }

    std::unique_ptr<Environment> nextEnvironment = std::make_unique<Environment>(*currentEnvironment);
    if (!nextEnvironment->removeFunction(funcName, argCount)) {
        throw std::invalid_argument("function undefining failed");
    }

    nextEnvironment->setPreviousEnvironment(std::move(currentEnvironment));
    currentEnvironment = std::move(nextEnvironment);

    std::cout << "undefining function <" << funcName << '(' << argCount << ")>\n";
}

void Interpreter::evaluateExpression(std::vector<Token>&& tokens) const {
    ObjectFactory factory(std::move(tokens), *currentEnvironment);

    auto expr = factory.createExpression();
    auto res = expr->evaluate();

    //std::cout << res->toString() << " <- " << expr->toString() << '\n';
    std::cout << res->toString() << '\n';
}

bool Interpreter::isValidFunctionDefinition(const std::vector<Token>& tokens) const {
    if (tokens.size() < 7) {
        return false;
    } else if (tokens[0].type != TokenType::Word || tokens[0].payload != KEYWORD_DEFINE_FUNCTION) {
        return false;
    } else if (tokens[1].type != TokenType::Word) {
        return false;
    } else if (tokens[2].type != TokenType::OpenCircleBracket) {
        return false;
    } else if (tokens[3].type != TokenType::Number) {
        return false;
    } else if (tokens[4].type != TokenType::CloseCircleBracket) {
        return false;
    } else if (tokens[5].type != TokenType::Equal) {
        return false;
    }

    return true;
}

bool Interpreter::isValidFunctionRedefinition(const std::vector<Token>& tokens) const {
    if (tokens.size() < 7) {
        return false;
    } else if (tokens[0].type != TokenType::Word || tokens[0].payload != KEYWORD_REDEFINE_FUNCTION) {
        return false;
    } else if (tokens[1].type != TokenType::Word) {
        return false;
    } else if (tokens[2].type != TokenType::OpenCircleBracket) {
        return false;
    } else if (tokens[3].type != TokenType::Number) {
        return false;
    } else if (tokens[4].type != TokenType::CloseCircleBracket) {
        return false;
    } else if (tokens[5].type != TokenType::Equal) {
        return false;
    }

    return true;
}

bool Interpreter::isValidFunctionUndefinition(const std::vector<Token>& tokens) const {
    if (tokens.size() != 5) {
        return false;
    } else if (tokens[0].type != TokenType::Word || tokens[0].payload != KEYWORD_UNDEFINE_FUNCTION) {
        return false;
    } else if (tokens[1].type != TokenType::Word) {
        return false;
    } else if (tokens[2].type != TokenType::OpenCircleBracket) {
        return false;
    } else if (tokens[3].type != TokenType::Number) {
        return false;
    } else if (tokens[4].type != TokenType::CloseCircleBracket) {
        return false;
    }

    return true;
}
