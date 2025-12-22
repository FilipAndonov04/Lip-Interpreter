#pragma once
#include "Expression/Variable/Number/Real/RealNumber.h"
#include "Expression/Variable/List/Concrete/ConcreteList.h"
#include "Expression/Variable/List/Lazy/Finite/FiniteList.h"
#include "Expression/Variable/List/Lazy/Infinite/InfiniteList.h"

#include "Function/Wrapper/WrapperFunction.hpp"
#include "Function/Graph/GraphFunction.h"
#include "Function/Graph/Node/Literal/LiteralNode.h"
#include "Function/Graph/Node/Argument/ArgumentNode.h"
#include "Function/Graph/Node/Composite/CompositeNode.h"

#include <iostream>

struct Add {
	std::unique_ptr<Expression> operator()(const std::vector<const Expression*>& args) const {
		auto a1 = args[0]->evaluate();
		auto a2 = args[1]->evaluate();

		auto n1 = dynamic_cast<RealNumber*>(a1.get());
		auto n2 = dynamic_cast<RealNumber*>(a2.get());

		return RealNumber::of(n1->getValue() + n2->getValue());
	}
};

struct Sub {
	std::unique_ptr<Expression> operator()(const std::vector<const Expression*>& args) const {
		auto a1 = args[0]->evaluate();
		auto a2 = args[1]->evaluate();

		auto n1 = dynamic_cast<RealNumber*>(a1.get());
		auto n2 = dynamic_cast<RealNumber*>(a2.get());

		return RealNumber::of(n1->getValue() - n2->getValue());
	}
};

struct AddOne {
	std::unique_ptr<Expression> operator()(const std::vector<const Expression*>& args) const {
		auto a1 = args[0]->evaluate();

		auto n1 = dynamic_cast<RealNumber*>(a1.get());

		return RealNumber::of(n1->getValue() + 1);
	}
};

struct Mul {
	std::unique_ptr<Expression> operator()(const std::vector<const Expression*>& args) const {
		auto a1 = args[0]->evaluate();
		auto a2 = args[1]->evaluate();

		auto n1 = dynamic_cast<RealNumber*>(a1.get());
		auto n2 = dynamic_cast<RealNumber*>(a2.get());

		return RealNumber::of(n1->getValue() * n2->getValue());
	}
};

struct Equal {
	std::unique_ptr<Expression> operator()(const std::vector<const Expression*>& args) const {
		auto a1 = args[0]->evaluate();
		auto a2 = args[1]->evaluate();

		auto n1 = dynamic_cast<RealNumber*>(a1.get());
		auto n2 = dynamic_cast<RealNumber*>(a2.get());

		return RealNumber::of((int)n1->getValue() == (int)n2->getValue());
	}
};

struct If {
	std::unique_ptr<Expression> operator()(const std::vector<const Expression*>& args) const {
		auto a1 = args[0]->evaluate();
		auto n1 = dynamic_cast<RealNumber*>(a1.get());

		if (n1->getValue() != 0) {
			return args[1]->evaluate();
		} else {
			return args[2]->evaluate();
		}
	}
};

struct PrintHello {
	std::unique_ptr<Expression> operator()(const std::vector<const Expression*>& args) const {
		std::cout << "Hello\n";
		return RealNumber::of(67);
	}
};