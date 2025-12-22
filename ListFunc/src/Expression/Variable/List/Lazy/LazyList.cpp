#include "LazyList.h"
#include "Function/Function.h"
#include "Expression/Variable/List/Concrete/ConcreteList.h"

LazyList::LazyList(std::unique_ptr<Variable>&& initialElement, std::unique_ptr<Function>&& step) 
	: cachedElements(std::make_unique<ConcreteList>()), step(std::move(step)) {
	cachedElements->pushBack(std::move(initialElement));
}

LazyList::LazyList(std::unique_ptr<List>&& cachedElements, std::unique_ptr<Function>&& step) 
	: cachedElements(std::move(cachedElements)), step(std::move(step)) {}

void LazyList::cacheElement(size_t index) const {
	if (index < cachedElements->length()) {
		return;
	} else if (index >= length()) {
		index = length() - 1;
	}

	std::vector<const Expression*> args(1);
	for (size_t lastIndex = cachedElements->length() - 1; lastIndex < index; lastIndex++) {
		args[0] = &cachedElements->at(lastIndex);
		cachedElements->pushBack(Expression::evaluate(step->call(args)));
	}
}
