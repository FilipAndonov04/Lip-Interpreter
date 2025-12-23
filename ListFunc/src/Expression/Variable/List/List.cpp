#include "List.h"

#include <stdexcept>

std::unique_ptr<Variable> List::cloneVariable() const {
    return cloneList();
}

std::unique_ptr<Expression> List::back() const {
    return at(length() - 1);
}

void List::pushBack(std::unique_ptr<Expression>&& element) {
    insert(length(), std::move(element));
}

std::string List::toString() const {
    std::string s("[");

    for (size_t i = 0; i < length(); i++) {
        s.append(at(i)->toString()).append(i != length() - 1 ? ", " : "");
    }

    s.append("]");
    return s;
}

bool List::isEmpty() const {
    return length() == 0;
}

std::unique_ptr<Expression> List::operator[](size_t index) const {
    return at(index);
}

std::unique_ptr<Expression> List::front() const {
    return at(0);
}

void List::pushFront(std::unique_ptr<Expression>&& element) {
    insert(0, std::move(element));
}

void List::popFront() {
    erase(0);
}

void List::popBack() {
    erase(length() - 1);
}

std::unique_ptr<Expression> List::popFrontAndGet() {
    return eraseAndGet(0);
}

std::unique_ptr<Expression> List::popBackAndGet() {
    return eraseAndGet(length() - 1);
}

void List::assertNotEmpty() const {
    if (isEmpty()) {
        throw std::logic_error("empty list");
    }
}

void List::assertAccessIndex(size_t index) const {
    if (index >= length()) {
        throw std::out_of_range("index out of bound");
    }
}

void List::assertInsertIndex(size_t index) const {
    if (index > length()) {
        throw std::out_of_range("index out of bound");
    }
}
