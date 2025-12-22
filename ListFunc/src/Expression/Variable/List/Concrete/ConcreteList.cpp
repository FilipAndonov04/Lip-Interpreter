#include "ConcreteList.h"

ConcreteList::ConcreteList(std::vector<std::unique_ptr<Variable>>&& elements) 
    : elements(std::move(elements)) {}

size_t ConcreteList::length() const {
    return elements.size();
}

const Variable& ConcreteList::at(size_t index) const {
    assertAccessIndex(index);

    return *elements[index];
}

Variable& ConcreteList::at(size_t index) {
    assertAccessIndex(index);

    return *elements[index];
}

void ConcreteList::insert(size_t index, std::unique_ptr<Variable>&& element) {
    assertInsertIndex(index);

    elements.insert(elements.begin() + index, std::move(element));
}

void ConcreteList::erase(size_t index) {
    eraseAndGet(index);
}

std::unique_ptr<Variable> ConcreteList::eraseAndGet(size_t index) {
    assertNotEmpty();
    assertAccessIndex(index);

    auto element = std::move(elements[index]);
    elements.erase(elements.begin() + index);
    return element;
}

std::unique_ptr<List> ConcreteList::cloneList() const {
    std::vector<std::unique_ptr<Variable>> clonedElements;
    clonedElements.reserve(length());

    for (const auto& element : elements) {
        clonedElements.push_back(element->cloneVariable());
    }

    return std::make_unique<ConcreteList>(std::move(clonedElements));
}