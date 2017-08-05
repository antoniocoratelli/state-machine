#pragma once
#include <experimental/optional>

namespace antoniocoratelli {

class State;

typedef std::experimental::optional<State*> Transition;

} // antoniocoratelli
