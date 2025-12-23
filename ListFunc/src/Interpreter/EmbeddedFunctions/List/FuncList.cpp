#include "FuncList.h"
#include "Value/List/Lazy/Finite/FiniteList.h"
#include "Value/List/Lazy/Infinite/InfiniteList.h"
#include "Value/Number/RealNumber.h"
#include "Function/Wrapper/WrapperFunction.hpp"

#include <stdexcept>

struct AddConst {
    std::unique_ptr<Expression> operator()(const std::vector<const Expression*>& args) const {
        auto arg1 = args[0]->evaluate();
        auto n1 = static_cast<RealNumber*>(arg1.get());
        
        return RealNumber::of(n1->getValue() + value);
    }

    double value;
};

std::unique_ptr<Expression> FuncList::operator()(const std::vector<const Expression*>& args) const {
    if (args.size() == 3) {
        auto arg1 = args[0]->evaluate();
        auto arg2 = args[1]->evaluate();
        auto arg3 = args[2]->evaluate();

        if (arg1->type() != ExpressionType::Number || arg2->type() != ExpressionType::Number ||
            arg3->type() != ExpressionType::Number) {
            throw std::invalid_argument("list takes 3 real numbers");
        }

        auto n2 = static_cast<RealNumber*>(arg2.get());
        auto n3 = static_cast<RealNumber*>(arg3.get());

        auto step = std::make_unique<WrapperFunction<AddConst>>(1, AddConst{n2->getValue()});
        return std::make_unique<FiniteList>(std::move(arg1), std::move(step), n3->getValue());
    } else if (args.size() == 2) {
        auto arg1 = args[0]->evaluate();
        auto arg2 = args[1]->evaluate();

        if (arg1->type() != ExpressionType::Number || arg2->type() != ExpressionType::Number) {
            throw std::invalid_argument("list takes 2 real numbers");
        }

        auto n2 = static_cast<RealNumber*>(arg2.get());

        auto step = std::make_unique<WrapperFunction<AddConst>>(1, AddConst{n2->getValue()});
        return std::make_unique<InfiniteList>(std::move(arg1), std::move(step));
    } else if (args.size() == 1) {
        auto arg1 = args[0]->evaluate();

        if (arg1->type() != ExpressionType::Number) {
            throw std::invalid_argument("list takes 1 real numbers");
        }

        auto step = std::make_unique<WrapperFunction<AddConst>>(1, AddConst{1});
        return std::make_unique<InfiniteList>(std::move(arg1), std::move(step));
    }
}
