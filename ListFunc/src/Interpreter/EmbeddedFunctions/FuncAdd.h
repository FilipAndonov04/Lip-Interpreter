#pragma once
#include "Expression/Variable/Number/Real/RealNumber.h"
#include "Expression/Variable/List/Concrete/ConcreteList.h"
#include "Expression/Variable/List/Lazy/Finite/FiniteList.h"
#include "Expression/Variable/List/Lazy/Infinite/InfiniteList.h"
#include "Expression/FunctionCall/FunctionCall.h"

struct FuncAdd {
	std::unique_ptr<Expression> operator()(const std::vector<const Expression*>& args) const {
		auto a1 = args[0]->evaluate();
		auto a2 = args[1]->evaluate();

		auto n1 = dynamic_cast<RealNumber*>(a1.get());
		auto n2 = dynamic_cast<RealNumber*>(a2.get());

		return RealNumber::of(n1->getValue() + n2->getValue());
	}
};