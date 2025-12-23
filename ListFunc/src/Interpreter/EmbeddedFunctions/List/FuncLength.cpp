#include "FuncLength.h"
#include "Expression/Variable/List/List.h"
#include "Expression/Variable/Number/Real/RealNumber.h"

#include <stdexcept>

std::unique_ptr<Expression> FuncLength::operator()(const std::vector<const Expression*>& args) const {
    auto arg1 = args[0]->evaluate();

    if (!isList(arg1->type())) {
        throw std::invalid_argument("length argument must be a list");
    }

    auto l1 = static_cast<List*>(arg1.get());
    return RealNumber::of(l1->length());
}
