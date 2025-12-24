#include "FuncConcat.h"
#include "Expression/Expression.h"
#include "Value/List/List.h"

#include <stdexcept>

std::unique_ptr<Value> FuncConcat::operator()(const std::vector<const Expression*>& args) const {
    auto arg1 = args[0]->evaluate();
    auto arg2 = args[1]->evaluate();

    if (arg1->type() != ValueType::List || arg2->type() != ValueType::List) {
        throw std::invalid_argument("concat arguments must be a list");
    }

    auto l1 = static_cast<List*>(arg1.get());
    auto l2 = static_cast<List*>(arg2.get());

    for (size_t i = 0; i < l2->length(); i++) {
        l1->pushBack(l2->at(i));
    }

    return arg1;
}
