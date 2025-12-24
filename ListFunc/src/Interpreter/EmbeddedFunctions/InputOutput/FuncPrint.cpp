#include "FuncPrint.h"
#include "Expression/Expression.h"
#include "Value/Number/RealNumber.h"

#include <iostream>

std::unique_ptr<Value> FuncPrint::operator()(const std::vector<const Expression*>& args) const {
	auto arg1 = args[0]->evaluate();
	
	std::cout << arg1->toString() << '\n';

	return RealNumber::of(1);
}
