#ifndef ANTONIOCORATELLI_TRANSITION_H
#define ANTONIOCORATELLI_TRANSITION_H

#include <experimental/optional>

namespace antoniocoratelli {

class State;

typedef std::experimental::optional<State*> Transition;

} // antoniocoratelli

#endif
