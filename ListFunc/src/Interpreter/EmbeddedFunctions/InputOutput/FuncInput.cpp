#include "FuncInput.h"
#include "Expression/Expression.h"
#include "Value/Value.h"
#include "Interpreter/InputParsing/Tokenizer.h"
#include "Interpreter/InputParsing/ObjectFactory.h"

#include <iostream>

FuncInput::FuncInput(Environment& environment) 
	: environment(&environment) {}

std::unique_ptr<Value> FuncInput::operator()(const std::vector<const Expression*>& args) const {
	std::cout << "> ";

	std::string line;
	std::getline(std::cin, line);

	Tokenizer tokenizer(line);
	ObjectFactory factory(tokenizer.tokenize(), *environment);

	return factory.createExpression()->evaluate();
}
