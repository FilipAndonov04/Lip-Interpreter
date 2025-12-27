#include "FuncPrint.h"
#include "Interpreter/EmbeddedFunctions/EmbeddedUtils.h"
#include "Expression/Expression.h"
#include "Value/Number/RealNumber.h"

#include <iostream>

std::unique_ptr<Value> FuncPrint::operator()(const std::vector<const Expression*>& args) const {
	for (size_t i = 0; i < args.size(); i++) {
		std::cout << args[i]->evaluate()->toString();

		if (i != args.size() - 1) {
			std::cout << ", ";
		}
	}
	std::cout << '\n';

	return RealNumber::of(1);
}
