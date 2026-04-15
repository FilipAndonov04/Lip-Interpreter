#include "FiniteList.h"
#include "Expression/Expression.h"
#include "Value/FunctionObject/FunctionObject.h"

FiniteList::FiniteList(std::unique_ptr<Expression>&& initialElement,
                       std::unique_ptr<FunctionObject>&& step, size_t elementCount)
    : LazyList(std::move(initialElement), std::move(step)), elementCount(elementCount) {}

FiniteList::FiniteList(std::vector<std::unique_ptr<Value>>&& cachedElements, 
                       std::unique_ptr<FunctionObject>&& step, size_t elementCount)
    : LazyList(std::move(cachedElements), std::move(step)), elementCount(elementCount) {}

size_t FiniteList::length() const {
    return elementCount;
}

std::unique_ptr<Value> FiniteList::at(size_t index) const {
    assertAccessIndex(index);

    cacheElement(index);
    return cachedElements[index]->cloneValue();
}

void FiniteList::set(size_t index, std::unique_ptr<Value>&& element) {
    assertAccessIndex(index);

    cacheElement(index + 1);
    cachedElements[index] = std::move(element);
}

void FiniteList::insert(size_t index, std::unique_ptr<Value>&& element) {
    assertInsertIndex(index);

    cacheElement(index);
    cachedElements.insert(cachedElements.begin() + index, std::move(element));
    elementCount++;
}

void FiniteList::erase(size_t index) {
    assertNotEmpty();
    assertAccessIndex(index);

    if (index == length() - 1 && length() > cachedElements.size()) {
        elementCount--;
        return;
    }

    eraseAndGet(index);
}

std::unique_ptr<Value> FiniteList::eraseAndGet(size_t index) {
    assertNotEmpty();
    assertAccessIndex(index);

    cacheElement(index + 1);
    elementCount--;
    auto element = std::move(cachedElements[index]);
    cachedElements.erase(cachedElements.begin() + index);
    return element;
}

std::unique_ptr<List> FiniteList::cloneList() const {
    return std::make_unique<FiniteList>(cloneCachedElements(), step->cloneFunctionObject(), elementCount);
}