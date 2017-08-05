#pragma once
#include <antoniocoratelli/StateMachine.h>

namespace antoniocoratelli {
namespace onoffswitch {

/* Controllable Events forward declarations */

class EventTurnOn;
class EventTurnOff;

/* States */

class StateOn: public statemachine::State {
public:
    StateOn() { this->attach<EventTurnOff>(); }
    std::string name() override { return "StateOn"; }
    std::string info() override { return "Current can flow."; }
    statemachine::Transition update() override { return {}; }
};

class StateOff: public statemachine::State {
public:
    StateOff() { this->attach<EventTurnOn>(); }
    std::string name() override { return "StateOff"; }
    std::string info() override { return "Circuit is open."; }
    statemachine::Transition update() override { return {}; }
};

/* Controllable Events */

class EventTurnOn: public statemachine::ControllableEvent {
public:
    std::string name() override { return "TurnOn"; }
    statemachine::Transition execute() { return {new StateOn}; }
};

class EventTurnOff: public statemachine::ControllableEvent {
public:
    std::string name() override { return "TurnOff"; }
    statemachine::Transition execute() { return {new StateOff}; }
};

/* State Machine */

class OnOffSwitch: public statemachine::StateMachine {
public:
    OnOffSwitch(): StateMachine(std::make_unique<StateOff>()) {}
    std::string name() const override { return "OnOffSwitch::" + _current_state->name(); }
    std::string info() const override { return "{" + name() + "} " + _current_state->info(); }
};

} // onoffswitch
} // antoniocoratelli
