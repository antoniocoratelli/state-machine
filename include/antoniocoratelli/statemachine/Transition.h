#pragma once
#include <experimental/optional>

namespace antoniocoratelli {
namespace statemachine {

class State;

/**
 * Type of object that defines an optional state transition.
 * When the StateMachine receives a Transition object, the current state
 * is changed only if the Transition has its value defined.
 * @attention The ownership of the pointer is assumed to be relased to the
 *            receiver, which must handle its deallocation.
 */
typedef std::experimental::optional<State*> Transition;

} // statemachine
} // antoniocoratelli
