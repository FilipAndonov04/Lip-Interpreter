#include "FunctionCall.h"
#include "Expression/Variable/Variable.h"

FunctionCall::FunctionCall(FunctionRef functionRef)
    : functionRef(std::move(functionRef)) {}

FunctionCall::FunctionCall(FunctionRef functionRef, 
                           std::vector<std::unique_ptr<Expression>>&& args)
    : functionRef(std::move(functionRef)), args(std::move(args)) {}


std::unique_ptr<Variable> FunctionCall::evaluate() const {
    std::vector<const Expression*> argRefs;
    argRefs.reserve(args.size());

    for (const auto& arg : args) {
        argRefs.push_back(arg.get());
    }

    return Expression::evaluate(functionRef->call(argRefs));
}

ExpressionType FunctionCall::type() const {
    return ExpressionType::FunctionCall;
}

std::unique_ptr<Expression> FunctionCall::cloneExpression() const {
    std::vector<std::unique_ptr<Expression>> clonedArgs;
    clonedArgs.reserve(args.size());

    for (const auto& arg : args) {
        clonedArgs.push_back(arg->cloneExpression());
    }

    return std::make_unique<FunctionCall>(functionRef, std::move(clonedArgs));
}

std::string FunctionCall::toString() const {
    std::string s = "(" + functionRef.getName() + ", " + "(";

    for (size_t i = 0; i < args.size(); i++) {
        s.append(args[i]->toString()).append(i != args.size() - 1 ? ", " : "");
    }

    s.append("))");
    return s;
}
