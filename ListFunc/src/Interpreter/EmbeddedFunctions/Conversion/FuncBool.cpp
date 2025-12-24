#include "FuncBool.h"
#include "Expression/Expression.h"
#include "Value/Number/RealNumber.h"

#include <stdexcept>

std::unique_ptr<Value> FuncBool::operator()(const std::vector<const Expression*>& args) const {
	auto arg1 = args[0]->evaluate();

	if (arg1->type() != ValueType::Number) {
		throw std::invalid_argument("if's first argument is real number");
	}

	auto n1 = static_cast<const RealNumber*>(arg1.get());
	return RealNumber::of(static_cast<bool>(n1->getValue()));
}
