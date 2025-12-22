#include "FiniteList.h"
#include "Function/Function.h"

FiniteList::FiniteList(std::unique_ptr<Variable>&& initialElement, 
                       std::unique_ptr<Function>&& step, size_t elementCount)
    : LazyList(std::move(initialElement), std::move(step)), elementCount(elementCount) {}

FiniteList::FiniteList(std::unique_ptr<List>&& cachedElements, 
                       std::unique_ptr<Function>&& step, size_t elementCount)
    : LazyList(std::move(cachedElements), std::move(step)), elementCount(elementCount) {}

size_t FiniteList::length() const {
    return elementCount;
}

const Variable& FiniteList::at(size_t index) const {
    assertAccessIndex(index);

    cacheElement(index);
    return cachedElements->at(index);
}

Variable& FiniteList::at(size_t index) {
    assertAccessIndex(index);

    cacheElement(index);
    return cachedElements->at(index);
}

void FiniteList::insert(size_t index, std::unique_ptr<Variable>&& element) {
    assertInsertIndex(index);

    cacheElement(index);
    cachedElements->insert(index, std::move(element));
    elementCount++;
}

void FiniteList::erase(size_t index) {
    assertNotEmpty();
    assertAccessIndex(index);

    if (index == length() - 1 && length() > cachedElements->length()) {
        elementCount--;
        return;
    }

    eraseAndGet(index);
}

std::unique_ptr<Variable> FiniteList::eraseAndGet(size_t index) {
    assertNotEmpty();
    assertAccessIndex(index);

    cacheElement(index + 1);
    elementCount--;
    return cachedElements->eraseAndGet(index);
}

std::unique_ptr<List> FiniteList::cloneList() const {
    return std::make_unique<FiniteList>(cachedElements->cloneList(), step->clone(), elementCount);
}