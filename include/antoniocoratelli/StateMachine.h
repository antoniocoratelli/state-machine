#ifndef ANTONIOCORATELLI_STATEMACHINE_H
#define ANTONIOCORATELLI_STATEMACHINE_H

#include <iostream>
#include <stdexcept>
#include <string>
#include "Event.h"
#include "State.h"
#include "Transition.h"

namespace antoniocoratelli {

class StateMachine {
public:

    StateMachine(State::uptr_t initial_state);

    virtual void update() final;

    template<class controllable_event_t> void trigger();

    virtual std::string name() const;

    virtual std::string info() const;

    template<class state_t> bool in() const;

protected:
    State::uptr_t _current_state;

private:
    void apply(Transition t);
};

} // antoniocoratelli

inline antoniocoratelli::StateMachine::StateMachine(State::uptr_t initial_state):
    _current_state(initial_state.release()) {
}

inline std::string antoniocoratelli::StateMachine::name() const {
    return _current_state->name();
}

inline std::string antoniocoratelli::StateMachine::info() const {
    return _current_state->info();
}

inline void antoniocoratelli::StateMachine::apply(Transition transition) {
    if(transition) {
        auto next_state = transition.value();
        std::cout << "{" << name() << "} Transitioning to: " << next_state->name() << std::endl;
        _current_state.reset(next_state);
    }
}

inline void antoniocoratelli::StateMachine::update() {
    this->apply(_current_state->update());
}

template<class state_t> inline bool antoniocoratelli::StateMachine::in() const {
    static_assert(std::is_base_of<State, state_t>::value);
    State* current = _current_state.get();
    state_t* current_casted = dynamic_cast<state_t*>(current);
    return current_casted != NULL;
}

template<class controllable_event_t> inline void antoniocoratelli::StateMachine::trigger() {
    static_assert(std::is_base_of<antoniocoratelli::ControllableEvent, controllable_event_t>::value);
    controllable_event_t event;
    if(_current_state->triggers<controllable_event_t>()) {
        this->apply(event.execute());
    } else {
        std::string e = event.name();
        std::string s = _current_state->name();
        throw std::logic_error("Event<" + e + "> can't be triggered in State<" + s + ">");
    }
}

#endif
