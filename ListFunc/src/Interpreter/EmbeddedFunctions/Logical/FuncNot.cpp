#include "FuncNot.h"
#include "Interpreter/EmbeddedFunctions/EmbeddedUtils.h"
#include "Expression/Expression.h"
#include "Value/Number/RealNumber.h"

#include <stdexcept>

std::unique_ptr<Value> FuncNot::operator()(const std::vector<const Expression*>& args) const {
	assertArgCount(1, args.size(), NAME);

	auto arg1 = args[0]->evaluate();
	return RealNumber::of(!toBool(*arg1));
}