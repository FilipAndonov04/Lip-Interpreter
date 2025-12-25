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

    for (size_t i = 0; i < elements.size(); i++) {
        s.append(elements[i]->toString()).append(i != elements.size() - 1 ? ", " : "");

        if (i + 1 == 15) {
            if (i != elements.size() - 1) {
                s.append("...");
            }
            break;
        }
    }

    s.append("]");
    return s;
}