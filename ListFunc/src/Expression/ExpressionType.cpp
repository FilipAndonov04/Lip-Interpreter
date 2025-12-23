#include "ExpressionType.h"

bool isVariable(ExpressionType type) {
	switch (type) {
	case ExpressionType::Variable:
	case ExpressionType::Number:
	case ExpressionType::List:
	case ExpressionType::ConcreteList:
	case ExpressionType::LazyList:
	case ExpressionType::FiniteList:
	case ExpressionType::InfiniteList:
		return true;
	case ExpressionType::FunctionCall:
	case ExpressionType::VariableCall:
		return false;
	}

	throw 0;
}

bool isList(ExpressionType type) {
	switch (type) {
	case ExpressionType::Variable:
	case ExpressionType::Number:
		return false;
	case ExpressionType::List:
	case ExpressionType::ConcreteList:
	case ExpressionType::LazyList:
	case ExpressionType::FiniteList:
	case ExpressionType::InfiniteList:
		return true;
	case ExpressionType::FunctionCall:
	case ExpressionType::VariableCall:
		return false;
	}

	throw 0;
}
