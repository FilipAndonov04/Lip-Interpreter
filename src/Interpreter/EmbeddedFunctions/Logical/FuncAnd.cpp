#include "FuncAnd.h"
#include "Interpreter/EmbeddedFunctions/EmbeddedUtils.h"
#include "Expression/Expression.h"
#include "Value/Number/RealNumber.h"

std::unique_ptr<Value> FuncAnd::operator()(const std::vector<const Expression*>& args) const {
	assertArgCount(2, args.size(), NAME);

	auto val1 = args[0]->evaluate();
	if (!toBool(*val1)) {
		return RealNumber::of(0);
	}

	auto val2 = args[1]->evaluate();
	return RealNumber::of(toBool(*val2));
}