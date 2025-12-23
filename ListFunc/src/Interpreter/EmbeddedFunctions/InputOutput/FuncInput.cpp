#include "FuncInput.h"
#include "Value/Number/RealNumber.h"
#include "Interpreter/InputParsing/Tokenizer.h"
#include "Interpreter/InputParsing/ObjectFactory.h"

#include <iostream>

FuncInput::FuncInput(const VariableSet& variableSet) 
	: variableSet(&variableSet) {}

std::unique_ptr<Expression> FuncInput::operator()(const std::vector<const Expression*>& args) const {
	std::cout << "> ";

	std::string line;
	std::getline(std::cin, line);

	Tokenizer tokenizer(line);
	ObjectFactory factory(tokenizer.tokenize(), *variableSet);

	return factory.createExpression();
}
