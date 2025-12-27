#include "FuncList.h"
#include "Interpreter/EmbeddedFunctions/EmbeddedUtils.h"
#include "Expression/Expression.h"
#include "Value/List/Lazy/Finite/FiniteList.h"
#include "Value/List/Lazy/Infinite/InfiniteList.h"
#include "Value/Number/RealNumber.h"
#include "Function/Wrapper/WrapperFunction.hpp"

#include <stdexcept>

static struct StepAddConst {
    std::unique_ptr<Value> operator()(const std::vector<const Expression*>& args) const {
        auto arg1 = args[0]->evaluate();
        auto n1 = getNumber(*arg1);
        
        return RealNumber::of(n1->getValue() + value);
    }

    double value;
};

std::unique_ptr<Value> FuncList::operator()(const std::vector<const Expression*>& args) const {
    if (args.size() == 1) {
        auto arg1 = args[0]->evaluate();
        if (!isNumber(*arg1)) {
            throw std::invalid_argument(NAME + " takes a number as a first argument");
        }
        
        auto step = std::make_unique<WrapperFunction<StepAddConst>>(1, StepAddConst{1});
        return std::make_unique<InfiniteList>(args[0]->clone(), std::move(step));
    } else if (args.size() == 2) {
        auto arg1 = args[0]->evaluate();
        if (!isNumber(*arg1)) {
            throw std::invalid_argument(NAME + " takes a number as a first argument");
        }

        auto arg2 = args[1]->evaluate();
        auto n2 = getNumber(*arg2);
        if (!n2) {
            throw std::invalid_argument(NAME + " takes a number as a second argument");
        }

        auto step = std::make_unique<WrapperFunction<StepAddConst>>(1, StepAddConst{n2->getValue()});
        return std::make_unique<InfiniteList>(args[0]->clone(), std::move(step));
    } else if (args.size() == 3) {
        auto arg1 = args[0]->evaluate();
        if (!isNumber(*arg1)) {
            throw std::invalid_argument(NAME + " takes a number as a first argument");
        }

        auto arg2 = args[1]->evaluate();
        auto n2 = getNumber(*arg2);
        if (!n2) {
            throw std::invalid_argument(NAME + " takes a number as a second argument");
        }
        
        auto arg3 = args[2]->evaluate();
        auto n3 = getNumber(*arg3);
        if (!n3) {
            throw std::invalid_argument(NAME + " takes a non-negative integer as a third argument");
        }

        auto i3 = static_cast<int>(n3->getValue());
        if (i3 < 0 || i3 != n3->getValue()) {
            throw std::invalid_argument(NAME + " takes a non-negative integer as a third argument");
        }

        auto step = std::make_unique<WrapperFunction<StepAddConst>>(1, StepAddConst{n2->getValue()});
        return std::make_unique<FiniteList>(args[0]->clone(), std::move(step), i3);
    }

    throw std::invalid_argument(NAME + " expects 1,2 or 3 arguments, but was called with " + 
                                std::to_string(args.size()));
}
