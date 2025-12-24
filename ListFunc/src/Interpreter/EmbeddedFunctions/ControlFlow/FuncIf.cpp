#include "FuncIf.h"
#include "Expression/Expression.h"
#include "Value/Number/RealNumber.h"

#include <stdexcept>

std::unique_ptr<Value> FuncIf::operator()(const std::vector<const Expression*>& args) const {
	auto arg1 = args[0]->evaluate();

	if (arg1->type() != ValueType::Number) {
		throw std::invalid_argument("if's first argument is real number");
	}

	auto n1 = static_cast<const RealNumber*>(arg1.get());
	return n1->getValue() ? args[1]->evaluate() : args[2]->evaluate();
}
