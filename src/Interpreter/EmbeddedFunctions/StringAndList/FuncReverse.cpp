#include "FuncReverse.h"
#include "Interpreter/EmbeddedFunctions/EmbeddedUtils.h"
#include "Expression/Expression.h"
#include "Value/List/List.h"
#include "Value/String/String.h"

#include <stdexcept>
#include <algorithm>

static void reverseString(String& s);
static void reverseList(List& l);

std::unique_ptr<Value> FuncReverse::operator()(const std::vector<const Expression*>& args) const {
    assertArgCount(1, args.size(), NAME);

    auto arg1 = args[0]->evaluate();
    auto l1 = getList(*arg1);
    auto s1 = getString(*arg1);
    if (!l1 && !s1) {
        throw std::invalid_argument(NAME + " takes a string or a list as an argument");
    }

    if (s1) {
        reverseString(*s1);
    } else {
        reverseList(*l1);
    }

    return arg1;
}

void reverseString(String& s) {
    std::reverse(s.getString().begin(), s.getString().end());
}

void reverseList(List& l) {
    const auto length = std::min(l.length(), MAX_LIST_COMPARISON_LENGTH);
    for (size_t i = 0; i < length / 2; i++) {
        auto elem = l.at(i);
        auto elem2 = l.at(length - 1 - i);

        l.set(length - 1 - i, std::move(elem));
        l.set(i, std::move(elem2));
    }
}