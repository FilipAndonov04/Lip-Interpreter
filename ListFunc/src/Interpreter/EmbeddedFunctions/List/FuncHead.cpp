#include "FuncHead.h"
#include "Value/List/List.h"

#include <stdexcept>

std::unique_ptr<Expression> FuncHead::operator()(const std::vector<const Expression*>& args) const {
    auto arg1 = args[0]->evaluate();

    if (!isList(arg1->type())) {
        throw std::invalid_argument("head argument must be a list");
    }

    auto l1 = static_cast<List*>(arg1.get());
    return l1->front();
}
