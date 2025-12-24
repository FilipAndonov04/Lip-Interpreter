#include "FuncTail.h"
#include "Expression/Expression.h"
#include "Value/List/List.h"

#include <stdexcept>

std::unique_ptr<Value> FuncTail::operator()(const std::vector<const Expression*>& args) const {
    auto arg1 = args[0]->evaluate();
    
    if (arg1->type() != ValueType::List) {
        throw std::invalid_argument("tail argument must be a list");
    }

    auto l1 = static_cast<List*>(arg1.get());
    l1->popFront();
    return arg1;
}
