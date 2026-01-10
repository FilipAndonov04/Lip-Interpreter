#include "FuncRead.h"
#include "Interpreter/EmbeddedFunctions/EmbeddedUtils.h"
#include "Expression/Expression.h"
#include "Value/List/Concrete/ConcreteList.h"
#include "Value/String/String.h"

#include <fstream>

std::unique_ptr<Value> FuncRead::operator()(const std::vector<const Expression*>& args) const {
	assertArgCount(1, args.size(), NAME);

	auto val = args[0]->evaluate();
	auto filename = getString(*val);
	if (!filename) {
		throw std::invalid_argument(NAME + " takes a filename as an argument");
	}

	auto lines = std::make_unique<ConcreteList>();

	std::ifstream ifs(filename->getString());
	if (!ifs.is_open()) {
		return lines;
	}

	std::string line;
	while (std::getline(ifs, line)) {
		lines->pushBack(String::of(std::move(line)));
	}

	return lines;
}