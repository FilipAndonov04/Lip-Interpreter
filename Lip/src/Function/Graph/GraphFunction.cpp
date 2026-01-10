#include "GraphFunction.h"
#include "Function/Graph/Node/FunctionNode.h"
#include "Expression/Expression.h"
#include "Value/Value.h"

GraphFunction::GraphFunction(std::unique_ptr<FunctionNode>&& graphRoot)
    : graphRoot(std::move(graphRoot)) {}

std::unique_ptr<Function> GraphFunction::clone() const {
    return std::make_unique<GraphFunction>(graphRoot->clone());
}

void GraphFunction::setGraphRoot(std::unique_ptr<FunctionNode>&& graphRoot) {
    this->graphRoot = std::move(graphRoot);
}

std::unique_ptr<Value> GraphFunction::callImpl(const std::vector<const Expression*>& args) const {
    return graphRoot->call(args)->evaluate();
}