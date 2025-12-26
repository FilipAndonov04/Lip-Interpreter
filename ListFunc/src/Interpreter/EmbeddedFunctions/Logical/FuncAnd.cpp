#include "FuncAnd.h"
#include "Expression/Expression.h"
#include "Value/Number/RealNumber.h"

#include <stdexcept>

static bool toBool(const Value& value);

std::unique_ptr<Value> FuncAnd::operator()(const std::vector<const Expression*>& args) const {
	auto val1 = args[0]->evaluate();
	if (!toBool(*val1)) {
		return RealNumber::of(0);
	}

	auto val2 = args[1]->evaluate();
	return RealNumber::of(toBool(*val2));
}

bool toBool(const Value& value) {
	if (value.type() == ValueType::Number) {
		auto num = static_cast<const RealNumber*>(&value);
		return num->getValue();
	}

	return false;
}
