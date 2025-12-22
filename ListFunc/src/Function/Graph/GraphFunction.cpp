#include "GraphFunction.h"
#include "Function/Graph/Node/FunctionNode.h"
#include "Expression/Variable/Variable.h"

GraphFunction::GraphFunction(size_t argCount, std::unique_ptr<FunctionNode>&& graphRoot) 
    : Function(argCount), graphRoot(std::move(graphRoot)) {}

std::unique_ptr<Function> GraphFunction::clone() const {
    return std::make_unique<GraphFunction>(getArgCount(), graphRoot->clone());
}

std::unique_ptr<Expression> GraphFunction::callImpl(const std::vector<const Expression*>& args) const {
    return graphRoot->call(args);
}