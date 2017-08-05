#pragma once
#include <experimental/optional>

namespace antoniocoratelli {
namespace statemachine {

class State;

typedef std::experimental::optional<State*> Transition;

} // statemachine
} // antoniocoratelli
