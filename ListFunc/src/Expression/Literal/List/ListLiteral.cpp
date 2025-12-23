#include "ListLiteral.h"
#include "Value/List/Concrete/ConcreteList.h"

#include <stdexcept>

ListLiteral::ListLiteral(std::vector<std::unique_ptr<Expression>>&& elements) 
    : elements(std::move(elements)) {}

std::unique_ptr<Value> ListLiteral::evaluate() const {
    std::vector<std::unique_ptr<Value>> values;
    values.reserve(elements.size());

    for (const auto& element : elements) {
        values.push_back(element->evaluate());
    }

    return std::make_unique<ConcreteList>(std::move(values));
}

ExpressionType ListLiteral::type() const {
    return ExpressionType::ListLiteral;
}

std::unique_ptr<Expression> ListLiteral::clone() const {
    std::vector<std::unique_ptr<Expression>> clonedElements;
    clonedElements.reserve(elements.size());

    for (const auto& element : elements) {
        clonedElements.push_back(element->clone());
    }

    return std::make_unique<ListLiteral>(std::move(clonedElements));
}

std::string ListLiteral::toString() const {
    std::string s("[");

    for (size_t i = 0; i < length(); i++) {
        s.append(at(i).toString()).append(i != length() - 1 ? ", " : "");

        if (i + 1 == 15) {
            if (i != length() - 1) {
                s.append("...");
            }
            break;
        }
    }

    s.append("]");
    return s;
}

size_t ListLiteral::length() const {
    return elements.size();
}

bool ListLiteral::isEmpty() const {
    return length() == 0;
}

const Expression& ListLiteral::at(size_t index) const {
    if (index >= length()) {
        throw std::out_of_range("index out of bound");
    }

    return *elements[index];
}

const Expression& ListLiteral::operator[](size_t index) const {
    return at(index);
}

const Expression& ListLiteral::front() const {
    return at(0);
}

const Expression& ListLiteral::back() const {
    return at(length() - 1);
}
