#ifndef ANTONIOCORATELLI_STATEMACHINE_STATEMACHINE_H
#define ANTONIOCORATELLI_STATEMACHINE_STATEMACHINE_H

namespace antoniocoratelli {

    class State; // Forward declaration needed for Transition

    class Transition : public std::optional<State> {
    };

    class State {
    };

    class StateMachine {
    };

}

#endif
