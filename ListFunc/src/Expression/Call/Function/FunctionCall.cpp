#include "FunctionCall.h"
#include "Value/Value.h"
#include "Function/Function.h"

FunctionCall::FunctionCall(const Function* function)
    : function(function) {}

FunctionCall::FunctionCall(const Function* function,
                           std::vector<std::unique_ptr<Expression>>&& args)
    : function(function), args(std::move(args)) {}


std::unique_ptr<Value> FunctionCall::evaluate() const {
    return function->call(getArgs());
}

std::unique_ptr<Expression> FunctionCall::cloneExpression() const {
    std::vector<std::unique_ptr<Expression>> clonedArgs;
    clonedArgs.reserve(args.size());

    for (const auto& arg : args) {
        clonedArgs.push_back(arg->cloneExpression());
    }

    return std::make_unique<FunctionCall>(function, std::move(clonedArgs));
}

std::string FunctionCall::toString() const {
    std::string s = "(" + std::string("<insert name>") + ", " + "(";

    for (size_t i = 0; i < args.size(); i++) {
        s.append(args[i]->toString()).append(i != args.size() - 1 ? ", " : "");
    }

    s.append("))");
    return s;
}

const Function* FunctionCall::getFunction() const {
    return function;
}

std::vector<const Expression*> FunctionCall::getArgs() const {
    std::vector<const Expression*> argRefs;
    argRefs.reserve(args.size());

    for (const auto& arg : args) {
        argRefs.push_back(arg.get());
    }

    return argRefs;
}
