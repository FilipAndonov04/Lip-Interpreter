#include "FuncWrite.h"
#include "Interpreter/EmbeddedFunctions/EmbeddedUtils.h"
#include "Expression/Expression.h"
#include "Value/String/String.h"
#include "Value/Number/RealNumber.h"

#include <fstream>

std::unique_ptr<Value> FuncWrite::operator()(const std::vector<const Expression*>& args) const {
	assertArgCount(3, args.size(), NAME);

	auto val1 = args[0]->evaluate();
	auto filename = getString(*val1);
	if (!filename) {
		throw std::invalid_argument(NAME + " takes a filename as a first argument");
	}

	auto val2 = args[1]->evaluate();

	auto val3 = args[2]->evaluate();
	auto num3 = getNumber(*val3);
	if (!num3) {
		throw std::invalid_argument(NAME + " takes a number as a third argument");
	}
	
	std::ofstream ofs(filename->getString(), toBool(*num3) ? std::ios::trunc : std::ios::app);
	if (!ofs.is_open()) {
		return RealNumber::of(0.0);
	}

	ofs << toString(*val2);

	return RealNumber::of(1.0);
}