#include "InfiniteList.h"
#include "Expression/Expression.h"
#include "Value/FunctionObject/FunctionObject.h"

#include <stdexcept>

InfiniteList::InfiniteList(std::unique_ptr<Expression>&& initialElement, 
                           std::unique_ptr<FunctionObject>&& step)
    : LazyList(std::move(initialElement), std::move(step)) {}

InfiniteList::InfiniteList(std::unique_ptr<List>&& cachedElements, 
                           std::unique_ptr<FunctionObject>&& step)
    : LazyList(std::move(cachedElements), std::move(step)) {}

size_t InfiniteList::length() const {
    constexpr size_t INFINITE_LENGTH = -1;
    return INFINITE_LENGTH;
}

std::unique_ptr<Value> InfiniteList::at(size_t index) const {
    cacheElement(index);
    return cachedElements->at(index);
}

std::unique_ptr<Value> InfiniteList::back() const {
    throw std::logic_error("infinite list does not have a last element");
}

void InfiniteList::set(size_t index, std::unique_ptr<Value>&& element) {
    cacheElement(index + 1);
    cachedElements->set(index, std::move(element));
}

void InfiniteList::insert(size_t index, std::unique_ptr<Value>&& element) {
    cacheElement(index);
    cachedElements->insert(index, std::move(element));
}

void InfiniteList::pushBack(std::unique_ptr<Value>&& element) {}

void InfiniteList::erase(size_t index) {
    eraseAndGet(index);
}

void InfiniteList::popBack() {}

std::unique_ptr<Value> InfiniteList::eraseAndGet(size_t index) {
    cacheElement(index + 1);
    return cachedElements->eraseAndGet(index);
}

std::unique_ptr<Value> InfiniteList::popBackAndGet() {
    throw std::logic_error("infinite list does not have a last element");
}

std::unique_ptr<List> InfiniteList::cloneList() const {
    return std::make_unique<InfiniteList>(cachedElements->cloneList(), step->cloneFunctionObject());
}
