#include "InfiniteList.h"
#include "Function/Function.h"

#include <stdexcept>

InfiniteList::InfiniteList(std::unique_ptr<Expression>&& initialElement, std::unique_ptr<Function>&& step)
    : LazyList(std::move(initialElement), std::move(step)) {}

InfiniteList::InfiniteList(std::unique_ptr<List>&& cachedElements, std::unique_ptr<Function>&& step)
    : LazyList(std::move(cachedElements), std::move(step)) {}

size_t InfiniteList::length() const {
    constexpr size_t INFINITE_LENGTH = -1;
    return INFINITE_LENGTH;
}

std::unique_ptr<Expression> InfiniteList::at(size_t index) const {
    cacheElement(index);
    return cachedElements->at(index);
}

void InfiniteList::insert(size_t index, std::unique_ptr<Expression>&& element) {
    cacheElement(index);
    cachedElements->insert(index, std::move(element));
}

void InfiniteList::pushBack(std::unique_ptr<Expression>&& element) {}

void InfiniteList::erase(size_t index) {
    eraseAndGet(index);
}

void InfiniteList::popBack() {}

std::unique_ptr<Expression> InfiniteList::eraseAndGet(size_t index) {
    cacheElement(index + 1);
    return cachedElements->eraseAndGet(index);
}

std::unique_ptr<Expression> InfiniteList::popBackAndGet() {
    throw std::logic_error("infinite list does not have a last element");
}

ExpressionType InfiniteList::type() const {
    return ExpressionType::InfiniteList;
}

std::unique_ptr<List> InfiniteList::cloneList() const {
    return std::make_unique<InfiniteList>(cachedElements->cloneList(), step->clone());
}
