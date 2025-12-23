#include "ObjectFactory.h"
#include "Expression/Variable/Number/RealNumber.h"
#include "Expression/Variable/List/Concrete/ConcreteList.h"
#include "Function/Graph/GraphFunction.h"
#include "Function/Graph/Node/FunctionNode.h"

#include "StringUtils/StringUtils.h"
#include "StringUtils/CharUtils.h"

#include <stdexcept>

ObjectFactory::ObjectFactory(std::vector<std::string> tokens, const VariableSet& variableSet, size_t index)
    : tokens(std::move(tokens)), variableSet(&variableSet), index(index) {}

std::unique_ptr<Expression> ObjectFactory::createExpression() {
    assertIndex();

    if (StringUtils::isLetter(tokens[index].front())) {
        return createFunctionCall();
    } else if (tokens[index] == "{") {
        return createVariableCall();
    }

    return createVariable();
}

std::unique_ptr<Variable> ObjectFactory::createVariable() {
    assertIndex();

    if (StringUtils::isDigit(tokens[index].front()) || StringUtils::isDash(tokens[index].front())) {
        return createRealNumber();
    } else if (tokens[index] == "[") {
        return createConcreteList();
    }

    throw std::invalid_argument("invalid token for variable");
}

std::unique_ptr<Function> ObjectFactory::createFunction(size_t argCount) {
    argIds.clear();
    return createGraphFunction(argCount);
}

std::unique_ptr<RealNumber> ObjectFactory::createRealNumber() {
    double value = StringUtils::toDouble(tokens[index++]);
    return RealNumber::of(value);
}

std::unique_ptr<ConcreteList> ObjectFactory::createConcreteList() {
    index++;

    assertIndex();
    if (tokens[index] == "]") {
        index++;
        return std::make_unique<ConcreteList>();
    }

    auto list = std::make_unique<ConcreteList>();
    list->pushBack(createExpression());

    while (true) {
        assertIndex();

        if (tokens[index] == "]") {
            index++;
            return list;
        }

        if (tokens[index++] != ",") {
            throw std::invalid_argument("invalid token for list");
        }
        list->pushBack(createExpression());
    }
}

std::unique_ptr<FunctionCall> ObjectFactory::createFunctionCall() {
    std::string functionName = std::move(tokens[index++]);

    assertIndex();
    if (tokens[index++] != "(") {
        throw std::invalid_argument("function name must be followed by a circle bracket");
    }

    assertIndex();
    if (tokens[index] == ")") {
        index++;
        return std::make_unique<FunctionCall>(FunctionRef{std::move(functionName), 0, *variableSet});
    }

    std::vector<std::unique_ptr<Expression>> args;
    args.push_back(createExpression());

    while (true) {
        assertIndex();

        if (tokens[index] == ")") {
            index++;
            return std::make_unique<FunctionCall>(FunctionRef{std::move(functionName), 
                                                  args.size(), *variableSet}, std::move(args));
        }

        if (tokens[index++] != ",") {
            throw std::invalid_argument("function arguments must be separated by commas");
        }
        args.push_back(createExpression());
    }
}

std::unique_ptr<VariableCall> ObjectFactory::createVariableCall() {
    index++;

    assertIndex();
    std::string variableName = std::move(tokens[index++]);

    assertIndex();
    if (tokens[index++] != "}") {
        throw std::invalid_argument("variable name must be followed by closed curly bracket");
    }

    return std::make_unique<VariableCall>(VariableRef{std::move(variableName), *variableSet});
}

std::unique_ptr<GraphFunction> ObjectFactory::createGraphFunction(size_t argCount) {
    auto root = createFunctionNode();
    if (argIds.size() != argCount || !argIds.empty() && *std::max_element(argIds.begin(), argIds.end()) != argCount) {
        throw std::invalid_argument("invalid argument count in function definition");
    }
    return std::make_unique<GraphFunction>(argIds.size(), std::move(root));
}

std::unique_ptr<FunctionNode> ObjectFactory::createFunctionNode() {
    assertIndex();

    if (tokens[index] == "$") {
        index++;
        assertIndex();
        index--;

        if (StringUtils::isDigit(tokens[index + 1].front())) {
            return createArgumentNode();
        } else if (StringUtils::isLetter(tokens[index + 1].front())) {
            return createVariableNode();
        }
        
        throw std::invalid_argument("$ must be followed by a argument number or variable name");
    } else if (StringUtils::isDigit(tokens[index].front()) || 
               StringUtils::isDash(tokens[index].front()) || 
               StringUtils::isOpenSquareBracket(tokens[index].front())) {
        return createLiteralNode();
    } else if (StringUtils::isLetter(tokens[index].front())) {
        return createCompositeNode();
    }
}

std::unique_ptr<ArgumentNode> ObjectFactory::createArgumentNode() {
    index++;

    assertIndex();
    size_t id = StringUtils::toSizeType(tokens[index++]);
    argIds.insert(id);
    return ArgumentNode::of(id);
}

std::unique_ptr<LiteralNode> ObjectFactory::createLiteralNode() {
    return LiteralNode::of(createVariable());
}

std::unique_ptr<CompositeNode> ObjectFactory::createCompositeNode() {
    std::string functionName = std::move(tokens[index++]);

    assertIndex();
    if (tokens[index++] != "(") {
        throw std::invalid_argument("function name must be followed by a circle bracket");
    }

    assertIndex();
    if (tokens[index] == ")") {
        index++;
        return std::make_unique<CompositeNode>(FunctionRef{std::move(functionName), 0, *variableSet});
    }

    std::vector<std::unique_ptr<FunctionNode>> argNodes;
    argNodes.push_back(createFunctionNode());

    while (true) {
        assertIndex();

        if (tokens[index] == ")") {
            index++;
            return std::make_unique<CompositeNode>(FunctionRef{std::move(functionName),
                                                  argNodes.size(), *variableSet}, std::move(argNodes));
        }

        if (tokens[index++] != ",") {
            throw std::invalid_argument("function arguments must be separated by commas");
        }
        argNodes.push_back(createFunctionNode());
    }
}

std::unique_ptr<VariableNode> ObjectFactory::createVariableNode() {
    index++;

    assertIndex();
    return VariableNode::of(VariableRef{std::move(tokens[index++]), *variableSet});
}

void ObjectFactory::assertIndex() const {
    if (index >= tokens.size()) {
        throw std::invalid_argument("there are no more tokens");
    }
}
