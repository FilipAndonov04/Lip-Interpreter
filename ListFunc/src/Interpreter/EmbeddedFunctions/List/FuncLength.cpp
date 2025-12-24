#include "FuncLength.h"
#include "Expression/Expression.h"
#include "Value/List/List.h"
#include "Value/Number/RealNumber.h"

#include <stdexcept>

std::unique_ptr<Value> FuncLength::operator()(const std::vector<const Expression*>& args) const {
    auto arg1 = args[0]->evaluate();

    if (arg1->type() != ValueType::List) {
        throw std::invalid_argument("length argument must be a list");
    }

    auto l1 = static_cast<List*>(arg1.get());
    return RealNumber::of(l1->length());
}
