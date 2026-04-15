#include "FuncConcat.h"
#include "Interpreter/EmbeddedFunctions/EmbeddedUtils.h"
#include "Expression/Expression.h"
#include "Value/List/List.h"
#include "Value/String/String.h"

#include <stdexcept>

static void concatStrings(String& s1, const String& s2);
static void concatLists(List& l1, const List& l2);

std::unique_ptr<Value> FuncConcat::operator()(const std::vector<const Expression*>& args) const {
    assertArgCount(2, args.size(), NAME);
    
    auto arg1 = args[0]->evaluate();
    auto l1 = getList(*arg1);
    auto s1 = getString(*arg1);
    if (!l1 && !s1) {
        throw std::invalid_argument(NAME + " takes a string or a list as a first argument");
    }
    
    auto arg2 = args[1]->evaluate();
    auto l2 = getList(*arg2);
    auto s2 = getString(*arg2);
    if (!l2 && !s2) {
        throw std::invalid_argument(NAME + " takes a string or a list as a second argument");
    }

    if (arg1->type() != arg2->type()) {
        throw std::invalid_argument("cannot concat a string and a list");
    }

    if (s1) {
        concatStrings(*s1, *s2);
    } else {
        concatLists(*l1, *l2);
    }

    return arg1;
}

void concatStrings(String& s1, const String& s2) {
    s1.getString().append(s2.getString());
}

void concatLists(List& l1, const List& l2) {
    const auto length = std::min(l2.length(), MAX_LIST_COMPARISON_LENGTH);
    for (size_t i = 0; i < length; i++) {
        l1.pushBack(l2[i]);
    }
}