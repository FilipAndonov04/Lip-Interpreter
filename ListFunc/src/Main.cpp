#include "Interpreter/Interpreter.h"
#include "Function/Wrapper/WrapperFunction.hpp"
#include "Interpreter/EmbeddedFunctions/FuncAdd.h"
#include "Interpreter/EmbeddedFunctions/FuncSub.h"
#include "Interpreter/EmbeddedFunctions/FuncMul.h"
#include "Interpreter/EmbeddedFunctions/FuncIf.h"
#include "Interpreter/EmbeddedFunctions/FuncEq.h"

#include <iostream>
#include <string>
#include <fstream>

int main() {
	VariableSet varSet;
	varSet.add("add", std::make_unique<WrapperFunction<FuncAdd>>(2));
	varSet.add("sub", std::make_unique<WrapperFunction<FuncSub>>(2));
	varSet.add("mul", std::make_unique<WrapperFunction<FuncMul>>(2));
	varSet.add("if", std::make_unique<WrapperFunction<FuncIf>>(3));
	varSet.add("eq", std::make_unique<WrapperFunction<FuncEq>>(2));

	Interpreter inter(std::move(varSet));
	
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