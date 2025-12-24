#include "FuncAdd.h"
#include "Expression/Expression.h"
#include "Value/Number/RealNumber.h"

#include <stdexcept>

std::unique_ptr<Value> FuncAdd::operator()(const std::vector<const Expression*>& args) const {
	auto arg1 = args[0]->evaluate();
	auto arg2 = args[1]->evaluate();

	if (arg1->type() != ValueType::Number ||
		arg2->type() != ValueType::Number) {
		throw std::invalid_argument("add takes 2 real numbers as arguments");
	}

	auto n1 = static_cast<const RealNumber*>(arg1.get());
	auto n2 = static_cast<const RealNumber*>(arg2.get());
	return RealNumber::of(n1->getValue() + n2->getValue());
}
