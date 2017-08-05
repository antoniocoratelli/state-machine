#ifndef ANTONIOCORATELLI_ONOFFSWITCH_H
#define ANTONIOCORATELLI_ONOFFSWITCH_H

#include <antoniocoratelli/StateMachine.h>

namespace antoniocoratelli {

    /* ControllableEvents forward declarations */

    class EventTurnOn;
    class EventTurnOff;

    /* States */

    class StateOn: public State {
    public:
        StateOn() { this->attach<EventTurnOff>(); }
        std::string name() override { return "StateOn"; }
        std::string info() override { return "Current can flow."; }
        Transition update() override { return {}; }
    };

    class StateOff: public State {
    public:
        StateOff() { this->attach<EventTurnOn>(); }
        std::string name() override { return "StateOff"; }
        std::string info() override { return "Circuit is interrupted."; }
        Transition update() override { return {}; }
    };

    /* Events */

    class EventTurnOn: public ControllableEvent {
    public:
        std::string name() override { return "TurnOn"; }
        Transition execute() { return {new StateOn}; }
    };

    class EventTurnOff: public ControllableEvent {
    public:
        std::string name() override { return "TurnOff"; }
        Transition execute() { return {new StateOff}; }
    };

    /* State Machine */

    class OnOffSwitch: public StateMachine {
    public:
        OnOffSwitch(): StateMachine(std::make_unique<StateOff>()) {}
        std::string name() const override { return "OnOffSwitch::" + _current_state->name(); }
        std::string info() const override { return "{" + name() + "} " + _current_state->info(); }
    };
}

#endif
