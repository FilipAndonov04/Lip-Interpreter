#include "Interpreter/Interpreter.h"
#include "EmbeddedFuncs.h"

#include <iostream>
#include <string>
#include <fstream>

int main() {
	VariableSet varSet;
	varSet.add("add", std::make_unique<WrapperFunction<Add>>(2));
	varSet.add("sub", std::make_unique<WrapperFunction<Sub>>(2));
	varSet.add("mul", std::make_unique<WrapperFunction<Mul>>(2));
	varSet.add("if", std::make_unique<WrapperFunction<If>>(3));
	varSet.add("eq", std::make_unique<WrapperFunction<Equal>>(2));

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