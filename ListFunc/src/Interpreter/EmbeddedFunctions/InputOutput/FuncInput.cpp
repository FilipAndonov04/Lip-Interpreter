#include "FuncInput.h"
#include "Expression/Expression.h"
#include "Value/Value.h"
#include "Interpreter/InputParsing/Tokenizer.h"
#include "Interpreter/InputParsing/ObjectFactory.h"
#include "Interpreter/Interpreter.h"

#include <iostream>

FuncInput::FuncInput(Interpreter& interpreter)
	: interpreter(&interpreter) {}

std::unique_ptr<Value> FuncInput::operator()(const std::vector<const Expression*>& args) const {
	std::cout << "> ";

	std::string line;
	std::getline(std::cin, line);

	Tokenizer tokenizer(line);
	ObjectFactory factory(tokenizer.tokenize(), interpreter->getCurrentEnvironment());

	return factory.createExpression()->evaluate();
}
