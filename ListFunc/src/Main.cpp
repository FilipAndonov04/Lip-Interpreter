#include "Interpreter/Interpreter.h"
#include "Function/Wrapper/WrapperFunction.hpp"

#include "Interpreter/EmbeddedFunctions/Math/FuncAdd.h"
#include "Interpreter/EmbeddedFunctions/Math/FuncSubtract.h"
#include "Interpreter/EmbeddedFunctions/Math/FuncMultiply.h"
#include "Interpreter/EmbeddedFunctions/Math/FuncDivide.h"
#include "Interpreter/EmbeddedFunctions/Math/FuncMod.h"
#include "Interpreter/EmbeddedFunctions/Math/FuncSqrt.h"
#include "Interpreter/EmbeddedFunctions/Logical/FuncNot.h"
#include "Interpreter/EmbeddedFunctions/Logical/FuncAnd.h"
#include "Interpreter/EmbeddedFunctions/Logical/FuncOr.h"
#include "Interpreter/EmbeddedFunctions/Comparison/FuncLessThan.h"
#include "Interpreter/EmbeddedFunctions/Comparison/FuncEquals.h"
#include "Interpreter/EmbeddedFunctions/ControlFlow/FuncIf.h"
#include "Interpreter/EmbeddedFunctions/Conversion/FuncInt.h"

#include <iostream>
#include <string>
#include <fstream>

struct Worker {
	std::unique_ptr<Expression> operator()(const std::vector<const Expression*>& args) const {
		std::cout << "\tDoing work\n";

		return RealNumber::of(1);
	}
};

struct Eval {
	std::unique_ptr<Expression> operator()(const std::vector<const Expression*>& args) const {
		for (auto& arg : args) {
			arg->evaluate();
		}

		return RealNumber::of(1);
	}
};

static VariableSet setUpFunctions();

int main() {
	Interpreter inter(setUpFunctions());
	
	{
		std::ifstream ifs("functions.txt");
		std::string line;
		while (std::getline(ifs, line)) {
			inter.interpret(line);
		}
	}

	while (true) {
		std::cout << "input command: ";
		std::string line;
		std::getline(std::cin, line);

		if (line == "quit") {
			break;
		}

		inter.interpret(line);
	}
}

VariableSet setUpFunctions() {
	VariableSet varSet;

	varSet.add("add", std::make_unique<WrapperFunction<FuncAdd>>(2));
	varSet.add("sub", std::make_unique<WrapperFunction<FuncSubtract>>(2));
	varSet.add("mul", std::make_unique<WrapperFunction<FuncMultiply>>(2));
	varSet.add("div", std::make_unique<WrapperFunction<FuncDivide>>(2));
	varSet.add("mod", std::make_unique<WrapperFunction<FuncMod>>(2));
	varSet.add("sqrt", std::make_unique<WrapperFunction<FuncSqrt>>(1));

	varSet.add("not", std::make_unique<WrapperFunction<FuncNot>>(1));
	varSet.add("and", std::make_unique<WrapperFunction<FuncAnd>>(2));
	varSet.add("or", std::make_unique<WrapperFunction<FuncOr>>(2));

	varSet.add("eq", std::make_unique<WrapperFunction<FuncEquals>>(2));
	varSet.add("lt", std::make_unique<WrapperFunction<FuncLessThan>>(2));

	varSet.add("if", std::make_unique<WrapperFunction<FuncIf>>(3));

	varSet.add("int", std::make_unique<WrapperFunction<FuncInt>>(1));

	varSet.add("work", std::make_unique<WrapperFunction<Worker>>(0));

	varSet.add("eval", std::make_unique<WrapperFunction<Eval>>(0));
	varSet.add("eval", std::make_unique<WrapperFunction<Eval>>(1));
	varSet.add("eval", std::make_unique<WrapperFunction<Eval>>(2));
	varSet.add("eval", std::make_unique<WrapperFunction<Eval>>(3));
	varSet.add("eval", std::make_unique<WrapperFunction<Eval>>(4));
	varSet.add("eval", std::make_unique<WrapperFunction<Eval>>(5));
	varSet.add("eval", std::make_unique<WrapperFunction<Eval>>(6));

	return varSet;
}