#include "LazyList.h"
#include "Expression/Value/ValueExpression.h"
#include "Function/Function.h"
#include "Value/List/Concrete/ConcreteList.h"

LazyList::LazyList(std::unique_ptr<Expression>&& initialElement, std::unique_ptr<Function>&& step)
	: initialElement(std::move(initialElement)), step(std::move(step)), 
	  cachedElements(std::make_unique<ConcreteList>()) {}

LazyList::LazyList(std::unique_ptr<List>&& cachedElements, std::unique_ptr<Function>&& step) 
	: cachedElements(std::move(cachedElements)), step(std::move(step)) {}

void LazyList::cacheElement(size_t index) const {
	if (index < cachedElements->length() || isEmpty()) {
		return;
	} else if (index >= length()) {
		index = length() - 1;
	}

	if (initialElement) {
		cachedElements->pushBack(initialElement->evaluate());
		initialElement.reset();
	}

	std::vector<const Expression*> args(1);
	for (size_t lastIndex = cachedElements->length() - 1; lastIndex < index; lastIndex++) {
		auto expr = std::make_unique<ValueExpression>(cachedElements->at(lastIndex));
		args[0] = expr.get();

		cachedElements->pushBack(step->call(args));
	}
}
