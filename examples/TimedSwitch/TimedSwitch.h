#pragma once
#include <chrono>
#include <antoniocoratelli/StateMachine.h>

namespace antoniocoratelli {
namespace timedswitch {

using std::chrono::seconds;

/* Controllable Events forward declarations */

class EventTurnOn;
class EventTurnOff;

/* States */

class StateOff: public statemachine::State {
public:
    StateOff() { this->attach<EventTurnOn>(); }
    std::string name() override { return "StateOff"; }
    std::string info() override { return "Circuit is interrupted."; }
    statemachine::Transition update() override { return {}; }
};

class StateOn: public statemachine::State {
public:
    StateOn():
        _timer(15) {
        this->attach<EventTurnOff>();
    }

    std::string name() override {
        return "StateOn";
    }

    std::string info() override {
        std::string s = std::to_string(_timer.count());
        return "Current can flow (" + s + "s to reset).";
    }

    statemachine::Transition update() override {
        if(_timer-- > seconds(0)) return {};
        else return {new StateOff};
    }

private:
    seconds _timer;
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

/* NonControllable Events */

class EventTimeout: public statemachine::NonControllableEvent {
public:
    std::string name() override { return "Timeout"; }
    statemachine::Transition execute() { return {new StateOff}; }
};

/* State Machine */

class TimedSwitch: public statemachine::StateMachine {
public:
    TimedSwitch(): StateMachine(std::make_unique<StateOff>()) {}
    std::string name() const override { return "TimedSwitch::" + _current_state->name(); }
    std::string info() const override { return "{" + name() + "} " + _current_state->info(); }
};

} // timedswitch
} // antoniocoratelli
