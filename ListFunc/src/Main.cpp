#include "Expression/Variable/Number/Real/RealNumber.h"
#include "Expression/Variable/List/Concrete/ConcreteList.h"
#include "Expression/Variable/List/Lazy/Finite/FiniteList.h"
#include "Expression/Variable/List/Lazy/Infinite/InfiniteList.h"

#include "Function/Wrapper/WrapperFunction.hpp"
#include "Function/Graph/GraphFunction.h"
#include "Function/Graph/Node/Literal/LiteralNode.h"
#include "Function/Graph/Node/Argument/ArgumentNode.h"
#include "Function/Graph/Node/Composite/CompositeNode.h"

#include "Interpreter/VariableDatabase.h"
#include "Interpreter/LineParser.h"
#include "Interpreter/ObjectFactory.h"

#include "EmbeddedFuncs.h"

#include <iostream>

void print(const Expression& e) {
	std::cout << e.toString() << '\n';
}

std::vector<std::unique_ptr<Expression>> makeArgs(size_t size);

std::unique_ptr<Function> createFactorialFunction(const VariableDatabase& database);

void testRecursive();

int main() {
	while (true) {
		std::string line;
		std::getline(std::cin, line);

		LineParser parser(line);
		auto tok = parser.tokenize();

		std::cout << "tokens: ";
		for (auto& s : tok) {
			std::cout << '"' << s << '"' << ' ';
		}
		std::cout << '\n';

		ObjectFactory factory(std::move(tok));
		try {
			auto var = factory.createVariable();
			print(*var);
		} catch (const std::exception& e) {
			std::cout << e.what() << '\n';
		}
	}
}

std::vector<std::unique_ptr<Expression>> makeArgs(size_t size) {
	std::vector<std::unique_ptr<Expression>> args;

	while (size-- > 0) {
		double temp;
		std::cin >> temp;
		args.push_back(RealNumber::of(temp));
	}

	return args;
}

std::unique_ptr<Function> createFactorialFunction(const VariableDatabase& database) {
	auto arg1Node = ArgumentNode::of(1);
	auto lit0Node = LiteralNode::of(RealNumber::of(0));
	auto lit1Node = LiteralNode::of(RealNumber::of(1));

	std::vector<std::unique_ptr<FunctionNode>> children;
	children.push_back(arg1Node->clone());
	children.push_back(lit0Node->clone());
	auto eqNode = std::make_unique<CompositeNode>(FunctionRef{"eq", 2, database}, std::move(children));
	
	children = std::vector<std::unique_ptr<FunctionNode>>{};
	children.push_back(arg1Node->clone());
	children.push_back(lit1Node->clone());
	auto subNode = std::make_unique<CompositeNode>(FunctionRef{"sub", 2, database}, std::move(children));
	
	children = std::vector<std::unique_ptr<FunctionNode>>{};
	children.push_back(subNode->clone());
	auto facNode = std::make_unique<CompositeNode>(FunctionRef{"fac", 1, database}, std::move(children));
	
	children = std::vector<std::unique_ptr<FunctionNode>>{};
	children.push_back(arg1Node->clone());
	children.push_back(facNode->clone());
	auto mulNode = std::make_unique<CompositeNode>(FunctionRef{"mul", 2, database}, std::move(children));
	
	children = std::vector<std::unique_ptr<FunctionNode>>{};
	children.push_back(eqNode->clone());
	children.push_back(lit1Node->clone());
	children.push_back(mulNode->clone());
	auto ifNode = std::make_unique<CompositeNode>(FunctionRef{"if", 3, database}, std::move(children));

	return std::make_unique<GraphFunction>(1, ifNode->clone());
}

void testRecursive() {
	VariableDatabase database;

	database.add("if", std::make_unique<WrapperFunction<If>>(3));
	database.add("eq", std::make_unique<WrapperFunction<Equal>>(2));
	database.add("mul", std::make_unique<WrapperFunction<Mul>>(2));
	database.add("sub", std::make_unique<WrapperFunction<Sub>>(2));
	database.add("prt", std::make_unique<WrapperFunction<PrintHello>>(0));

	database.add("fac", createFactorialFunction(database));

	auto& f = database.getFunction("fac", 1);

	auto argOwns = makeArgs(1);
	std::vector<const Expression*> argRefs;
	for (const auto& arg : argOwns) {
		argRefs.push_back(arg.get());
	}

	auto res = f(argRefs)->evaluate();
	print(*res);
}
