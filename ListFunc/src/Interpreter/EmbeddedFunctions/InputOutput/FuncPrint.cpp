#include "FuncPrint.h"
#include "Value/Number/RealNumber.h"

#include <iostream>

std::unique_ptr<Expression> FuncPrint::operator()(const std::vector<const Expression*>& args) const {
	auto arg1 = args[0]->evaluate();
	
	std::cout << arg1->toString() << '\n';

	return RealNumber::of(1);
}
