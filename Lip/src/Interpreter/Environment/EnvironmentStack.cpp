#include "EnvironmentStack.h"

#include <stdexcept>

EnvironmentStack::EnvironmentStack(const EnvironmentStack& other) {
    if (!other.top) {
        return;
    }

    top = std::make_unique<EnvironmentNode>(other.top->environment);

    EnvironmentNode* current = top.get();
    EnvironmentNode* otherCurrent = other.top.get();
    while (otherCurrent->prev) {
        current->prev = std::make_unique<EnvironmentNode>(otherCurrent->prev->environment);
        
        current = current->prev.get();
        otherCurrent = otherCurrent->prev.get();
    }
}

EnvironmentStack& EnvironmentStack::operator=(const EnvironmentStack& other) {
    if (this != &other) {

    }
    return *this;
}

const Environment& EnvironmentStack::getCurrentEnvironment() const {
    assertNotEmpty();

    return top->environment;
}

Environment& EnvironmentStack::getCurrentEnvironment() {
    assertNotEmpty();

    return top->environment;
}

bool EnvironmentStack::isEmpty() const {
    return top.get();
}

void EnvironmentStack::pushEnvironment(const Environment& environment) {
    auto next = std::make_unique<EnvironmentNode>(environment);
    next->prev = std::move(top);
    top = std::move(next);
}

void EnvironmentStack::pushEnvironment(Environment&& environment) {
    auto next = std::make_unique<EnvironmentNode>(std::move(environment));
    next->prev = std::move(top);
    top = std::move(next);
}

Environment EnvironmentStack::popEnvironment() {
    assertNotEmpty();

    auto env = std::move(top->environment);
    top = std::move(top->prev);
    return env;
}

void EnvironmentStack::assertNotEmpty() const {
    if (isEmpty()) {
        throw std::logic_error("environment stack is empty");
    }
}

EnvironmentStack::EnvironmentNode::EnvironmentNode(const Environment& environment) 
    : environment(environment) {}

EnvironmentStack::EnvironmentNode::EnvironmentNode(Environment&& environment) 
    : environment(std::move(environment)) {}