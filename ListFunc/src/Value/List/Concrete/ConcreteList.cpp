#include "ConcreteList.h"

ConcreteList::ConcreteList(std::vector<std::unique_ptr<Value>>&& elements) 
    : elements(std::move(elements)) {}

size_t ConcreteList::length() const {
    return elements.size();
}

std::unique_ptr<Value> ConcreteList::at(size_t index) const {
    assertAccessIndex(index);

    return elements[index]->cloneValue();
}

void ConcreteList::insert(size_t index, std::unique_ptr<Value>&& element) {
    assertInsertIndex(index);

    elements.insert(elements.begin() + index, std::move(element));
}

void ConcreteList::erase(size_t index) {
    eraseAndGet(index);
}

std::unique_ptr<Value> ConcreteList::eraseAndGet(size_t index) {
    assertNotEmpty();
    assertAccessIndex(index);

    auto element = std::move(elements[index]);
    elements.erase(elements.begin() + index);
    return element;
}

std::unique_ptr<List> ConcreteList::cloneList() const {
    std::vector<std::unique_ptr<Value>> clonedElements;
    clonedElements.reserve(length());

    for (const auto& element : elements) {
        clonedElements.push_back(element->cloneValue());
    }

    return std::make_unique<ConcreteList>(std::move(clonedElements));
}