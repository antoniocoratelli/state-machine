#ifndef ANTONIOCORATELLI_STATEMACHINE_H
#define ANTONIOCORATELLI_STATEMACHINE_H

#include "State.h"
#include "Transition.h"

namespace antoniocoratelli
{
    class StateMachine
    {
    public:

        StateMachine(State::uptr_t initial_state);

        virtual void update() final;

        virtual std::string name() const;

        virtual std::string info() const;

        template<class state_t> bool inState() const;

    private:
        State::uptr_t _current_state;
    };
}

antoniocoratelli::StateMachine::StateMachine(State::uptr_t initial_state):
    _current_state(initial_state.release()) {
}

std::string antoniocoratelli::StateMachine::name() const {
    return _current_state->name();
}

std::string antoniocoratelli::StateMachine::info() const {
    return _current_state->info();
}

template<class state_t> bool antoniocoratelli::StateMachine::inState() const {
    static_assert(std::is_base_of<State, state_t>::value);
    return typeid(_current_state.get()) == typeid(state_t*);
}

void antoniocoratelli::StateMachine::update() {
    Transition transition = _current_state->update();
    if(transition.emitted()) {
        auto next_state = transition.destination().release();
        std::cout << __PRETTY_FUNCTION__ << " State transition: "
                  << _current_state->name() << " -> " << next_state->name() << std::endl;
        _current_state.reset(next_state);
    }
}

#endif
