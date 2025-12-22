#include "InfiniteList.h"
#include "Function/Function.h"

#include <stdexcept>

InfiniteList::InfiniteList(std::unique_ptr<Variable>&& initialElement, std::unique_ptr<Function>&& step) 
    : LazyList(std::move(initialElement), std::move(step)) {}

InfiniteList::InfiniteList(std::unique_ptr<List>&& cachedElements, std::unique_ptr<Function>&& step)
    : LazyList(std::move(cachedElements), std::move(step)) {}

size_t InfiniteList::length() const {
    constexpr size_t INFINITE_LENGTH = -1;
    return INFINITE_LENGTH;
}

const Variable& InfiniteList::at(size_t index) const {
    cacheElement(index);
    return cachedElements->at(index);
}

Variable& InfiniteList::at(size_t index) {
    cacheElement(index);
    return cachedElements->at(index);
}

void InfiniteList::insert(size_t index, std::unique_ptr<Variable>&& element) {
    cacheElement(index);
    cachedElements->insert(index, std::move(element));
}

void InfiniteList::pushBack(std::unique_ptr<Variable>&& element) {}

void InfiniteList::erase(size_t index) {
    eraseAndGet(index);
}

void InfiniteList::popBack() {}

std::unique_ptr<Variable> InfiniteList::eraseAndGet(size_t index) {
    cacheElement(index + 1);
    return cachedElements->eraseAndGet(index);
}

std::unique_ptr<Variable> InfiniteList::popBackAndGet() {
    throw std::logic_error("infinite list does not have a last element");
}

std::unique_ptr<List> InfiniteList::cloneList() const {
    return std::make_unique<InfiniteList>(cachedElements->cloneList(), step->clone());
}

std::string InfiniteList::toString() const {
    constexpr size_t ELEMENTS_TO_PRINT = 10;

    std::string s("[");

    for (size_t i = 0; i < ELEMENTS_TO_PRINT; i++) {
        s.append(at(i).toString()).append(i != ELEMENTS_TO_PRINT - 1 ? ", " : ", ...");
    }

    s.append("]");
    return s;
}
