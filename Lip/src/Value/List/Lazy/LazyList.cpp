#include "LazyList.h"
#include "Expression/Value/ValueExpression.h"
#include "Value/FunctionObject/FunctionObject.h"

LazyList::LazyList(std::unique_ptr<Expression>&& initialElement, std::unique_ptr<FunctionObject>&& step)
	: initialElement(std::move(initialElement)), step(std::move(step)) {}

LazyList::LazyList(std::vector<std::unique_ptr<Value>>&& cachedElements, std::unique_ptr<FunctionObject>&& step)
	: cachedElements(std::move(cachedElements)), step(std::move(step)) {}

void LazyList::cacheElement(size_t index) const {
	if (index < cachedElements.size() || isEmpty()) {
		return;
	} else if (index >= length()) {
		index = length() - 1;
	}

	if (initialElement) {
		cachedElements.push_back(initialElement->evaluate());
		initialElement.reset();
	}

	std::vector<const Expression*> args(1);
	for (size_t lastIndex = cachedElements.size() - 1; lastIndex < index; lastIndex++) {
		auto expr = std::make_unique<ValueExpression>(cachedElements[lastIndex]->cloneValue());
		args[0] = expr.get();

		cachedElements.push_back(step->call(args));
	}
}

std::vector<std::unique_ptr<Value>> LazyList::cloneCachedElements() const {
	std::vector<std::unique_ptr<Value>> clonedElements;
	clonedElements.reserve(length());

	for (const auto& element : cachedElements) {
		clonedElements.push_back(element->cloneValue());
	}

	return clonedElements;
}
