#pragma once
#include "Expression/Variable/Number/Real/RealNumber.h"
#include "Expression/Variable/List/Concrete/ConcreteList.h"
#include "Expression/Variable/List/Lazy/Finite/FiniteList.h"
#include "Expression/Variable/List/Lazy/Infinite/InfiniteList.h"
#include "Expression/FunctionCall/FunctionCall.h"

struct FuncMul {
	std::unique_ptr<Expression> operator()(const std::vector<const Expression*>& args) const;
};