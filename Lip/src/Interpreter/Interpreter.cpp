#include "Interpreter.h"
#include "Interpreter/InputParsing/Tokenizer/Tokenizer.h"
#include "Interpreter/InputParsing/Factory/ObjectFactory.h"
#include "Expression/Expression.h"
#include "Value/Value.h"

#include "Utils/StringUtils.h"

#include <iostream>

Interpreter::Interpreter() {
    environmentStack.pushEnvironment(Environment{});
}

void Interpreter::interpret(std::string_view line) {
    if (line.empty() || line.starts_with("//")) {
        return;
    }

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
        } else if (tokens[0].payload == KEYWORD_CREATE_VARIABLE) {
            createVariable(std::move(tokens));
        } else if (tokens[0].payload == KEYWORD_CREATE_CONST_VARIABLE) {
            createConstVariable(std::move(tokens));
        } else if (tokens[0].payload == KEYWORD_REMOVE_VARIABLE) {
            removeVariable(std::move(tokens));
        } else {
            evaluateExpression(std::move(tokens));
        }
    } catch (const std::exception& e) {
        std::cerr << Utils::RED << "[ERROR] " << e.what() << Utils::DEFAULT << '\n';
    }
}

const Environment& Interpreter::getCurrentEnvironment() const {
    return environmentStack.getCurrentEnvironment();
}

Environment& Interpreter::getCurrentEnvironment() {
    return environmentStack.getCurrentEnvironment();
}

void Interpreter::defineFunction(std::vector<Token>&& tokens) {
    if (!isValidFunctionDefinition(tokens)) {
        throw std::invalid_argument(std::string("defining function must be in the following format: ") +
                                    KEYWORD_DEFINE_FUNCTION + " <func_name>(<num_args>) = <func_body>");
    }

    std::string funcName = std::move(tokens[1].payload);
    size_t argCount = Utils::toSizeType(tokens[3].payload);
    if (isKeyword(funcName)) {
        throw std::invalid_argument("<" + funcName + "> is a language keyword");
    } if (getCurrentEnvironment().containsFunction(funcName, argCount)) {
        throw std::invalid_argument("function <" + funcName + "(" + 
                                    std::to_string(argCount) + ")> is already defined");
    } else if (getCurrentEnvironment().containsVariable(funcName)) {
        throw std::invalid_argument("there is a variable <" + funcName + ">");
    }

    Environment nextEnvironment(getCurrentEnvironment());

    ObjectFactory factory(std::move(tokens), nextEnvironment, 6);
    auto func = factory.createFunction(funcName, argCount);

    pushEnvironment(std::move(nextEnvironment));

    std::cout << "defining function <" << funcName << '(' << argCount << ")>\n";
}

void Interpreter::redefineFunction(std::vector<Token>&& tokens) {
    if (!isValidFunctionRedefinition(tokens)) {
        throw std::invalid_argument(std::string("redefining function must be in the following format: ") +
                                    KEYWORD_REDEFINE_FUNCTION + " <func_name>(<num_args>) = <func_body>");
    }

    std::string funcName = std::move(tokens[1].payload);
    size_t argCount = Utils::toSizeType(tokens[3].payload);
    if (!getCurrentEnvironment().containsFunction(funcName, argCount)) {
        throw std::invalid_argument("function <" + funcName +
                                    "(" + std::to_string(argCount) + ")> is not defined");
    }

    Environment nextEnvironment(getCurrentEnvironment());
    if (!nextEnvironment.removeFunction(funcName, argCount)) {
        throw std::invalid_argument("function redefining failed");
    }

    ObjectFactory factory(std::move(tokens), nextEnvironment, 6);
    auto func = factory.createFunction(funcName, argCount);

    pushEnvironment(std::move(nextEnvironment));

    std::cout << "redefining function <" << funcName << '(' << argCount << ")>\n";
}

void Interpreter::undefineFunction(std::vector<Token>&& tokens) {
    if (!isValidFunctionUndefinition(tokens)) {
        throw std::invalid_argument(std::string("undefining function must be in the following format: ") +
                                    KEYWORD_UNDEFINE_FUNCTION + " <func_name>(<num_args>)");
    }

    std::string funcName = std::move(tokens[1].payload);
    size_t argCount = Utils::toSizeType(tokens[3].payload);
    if (!getCurrentEnvironment().containsFunction(funcName, argCount)) {
        throw std::invalid_argument("function <" + funcName +
                                    "(" + std::to_string(argCount) + ")> was already not defined");
    }

    Environment nextEnvironment(getCurrentEnvironment());
    if (!nextEnvironment.removeFunction(funcName, argCount)) {
        throw std::invalid_argument("function undefining failed");
    }

    pushEnvironment(std::move(nextEnvironment));

    std::cout << "undefining function <" << funcName << '(' << argCount << ")>\n";
}

void Interpreter::createVariable(std::vector<Token>&& tokens) {
    if (!isValidVariableCreation(tokens)) {
        throw std::invalid_argument(std::string("creating variable must be in the following format: ") +
                                    KEYWORD_CREATE_VARIABLE + " <var_name> = <expr>");
    }

    std::string varName = std::move(tokens[1].payload);
    if (isKeyword(varName)) {
        throw std::invalid_argument("<" + varName + "> is a language keyword");
    } else if (getCurrentEnvironment().containsFunction(varName)) {
        throw std::invalid_argument("there exists a function <" + varName + ">");
    }

    auto varData = getCurrentEnvironment().getVariableData(varName);
    if (varData && varData->getIsConst()) {
        throw std::invalid_argument("there exists a constant <" + varName + ">");
    }

    Environment nextEnvironment(getCurrentEnvironment());

    ObjectFactory factory(std::move(tokens), nextEnvironment, 3);
    auto expr = factory.createExpression();
    auto var = std::make_unique<VariableData>(expr->evaluate(), false);
    
    bool isAdded = nextEnvironment.containsVariable(varName) ? 
        nextEnvironment.replaceVariable(varName, std::move(var)) :
        nextEnvironment.addVariable(varName, std::move(var));
    if (!isAdded) {
        throw std::invalid_argument("variable creation failed");
    }

    pushEnvironment(std::move(nextEnvironment));

    std::cout << "creating variable <" << varName << "> with value " << 
        getCurrentEnvironment().getVariable(varName)->toString() << '\n';
}

void Interpreter::createConstVariable(std::vector<Token>&& tokens) {
    if (!isValidConstVariableCreation(tokens)) {
        throw std::invalid_argument(std::string("creating constant must be in the following format: ") +
                                    KEYWORD_CREATE_CONST_VARIABLE + " <const_name> = <expr>");
    }

    std::string constName = std::move(tokens[1].payload);
    if (isKeyword(constName)) {
        throw std::invalid_argument("<" + constName + "> is a language keyword");
    } else if (getCurrentEnvironment().containsFunction(constName)) {
        throw std::invalid_argument("there exists a function <" + constName + ">");
    }

    auto varData = getCurrentEnvironment().getVariableData(constName);
    if (varData && varData->getIsConst()) {
        throw std::invalid_argument("there exists a constant <" + constName + ">");
    }

    Environment nextEnvironment(getCurrentEnvironment());

    ObjectFactory factory(std::move(tokens), nextEnvironment, 3);
    auto expr = factory.createExpression();
    auto var = std::make_unique<VariableData>(expr->evaluate(), true);
    
    bool isAdded = nextEnvironment.containsVariable(constName) ? 
        nextEnvironment.replaceVariable(constName, std::move(var)) :
        nextEnvironment.addVariable(constName, std::move(var));
    if (!isAdded) {
        throw std::invalid_argument("constant creation failed");
    }

    pushEnvironment(std::move(nextEnvironment));

    std::cout << "creating constant <" << constName << "> with value " <<
        getCurrentEnvironment().getVariable(constName)->toString() << '\n';
}

void Interpreter::removeVariable(std::vector<Token>&& tokens) {
    if (!isValidVariableRemoval(tokens)) {
        throw std::invalid_argument(std::string("removing variable must be in the following format: ") +
                                    KEYWORD_REMOVE_VARIABLE + " <var_name>");
    }

    std::string varName = std::move(tokens[1].payload);
    auto varData = getCurrentEnvironment().getVariableData(varName);
    if (varData && varData->getIsConst()) {
        throw std::invalid_argument("cannot remove a constant");
    } else if (!varData) {
        throw std::invalid_argument("variable <" + varName + "> does not exist");
    }

    Environment nextEnvironment(getCurrentEnvironment());
    if (!nextEnvironment.removeVariable(varName)) {
        throw std::invalid_argument("variable removal failed");
    }

    pushEnvironment(std::move(nextEnvironment));

    std::cout << "removing variable <" << varName << ">\n";
}

void Interpreter::evaluateExpression(std::vector<Token>&& tokens) {
    ObjectFactory factory(std::move(tokens), environmentStack.getCurrentEnvironment());

    auto expr = factory.createExpression();
    auto res = expr->evaluate();

    //std::cout << res->toString() << " <- " << expr->toString() << '\n';
    std::cout << "res = " << res->toString() << '\n';
}

bool Interpreter::isValidFunctionDefinition(const std::vector<Token>& tokens) const {
    if (tokens.size() <= 6) {
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
    if (tokens.size() <= 6) {
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

bool Interpreter::isValidVariableCreation(const std::vector<Token>& tokens) const {
    if (tokens.size() <= 3) {
        return false;
    } else if (tokens[0].type != TokenType::Word || 
               tokens[0].payload != KEYWORD_CREATE_VARIABLE) {
        return false;
    } else if (tokens[1].type != TokenType::Word) {
        return false;
    } else if (tokens[2].type != TokenType::Equal) {
        return false;
    }

    return true;
}

bool Interpreter::isValidConstVariableCreation(const std::vector<Token>& tokens) const {
    if (tokens.size() <= 3) {
        return false;
    } else if (tokens[0].type != TokenType::Word || 
               tokens[0].payload != KEYWORD_CREATE_CONST_VARIABLE) {
        return false;
    } else if (tokens[1].type != TokenType::Word) {
        return false;
    } else if (tokens[2].type != TokenType::Equal) {
        return false;
    }

    return true;
}

bool Interpreter::isValidVariableRemoval(const std::vector<Token>& tokens) const {
    if (tokens.size() != 2) {
        return false;
    } else if (tokens[0].type != TokenType::Word || tokens[0].payload != KEYWORD_REMOVE_VARIABLE) {
        return false;
    } else if (tokens[1].type != TokenType::Word) {
        return false;
    }

    return true;
}

bool Interpreter::isKeyword(std::string_view word) {
    return word == KEYWORD_DEFINE_FUNCTION || word == KEYWORD_REDEFINE_FUNCTION || 
        word == KEYWORD_UNDEFINE_FUNCTION ||  word == KEYWORD_CREATE_VARIABLE || 
        word == KEYWORD_CREATE_CONST_VARIABLE || word == KEYWORD_REMOVE_VARIABLE;
}

void Interpreter::pushEnvironment(const Environment& environment) {
    environmentStack.pushEnvironment(environment);
}

void Interpreter::pushEnvironment(Environment&& environment) {
    environmentStack.pushEnvironment(std::move(environment));
}