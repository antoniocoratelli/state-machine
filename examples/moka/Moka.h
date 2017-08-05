#pragma once
#include <chrono>
#include <antoniocoratelli/statemachine/StateMachine.h>

namespace antoniocoratelli {
namespace moka {

using std::chrono::minutes;

/* Controllable Events forward declarations */

class EventPutWater;
class EventPutGroundCoffee;
class EventTurnFireOn;
class EventTurnFireOff;
class EventServe;
class EventClean;

/* Controllable States */

class StateIdle: public statemachine::State {
public:
    StateIdle() {
        this->attach<EventPutWater>();
    }
    std::string name() override { return "StateIdle"; }
    std::string info() override { return "Clean and ready to prepare another coffee."; }
    statemachine::Transition update() override { return {}; }
};

class StateReadyForGroundCoffee: public statemachine::State {
public:
    StateReadyForGroundCoffee() {
        this->attach<EventPutGroundCoffee>();
        this->attach<EventClean>();
    }
    std::string name() override { return "StateReadyForGroundCoffee"; }
    std::string info() override { return "Waiting for ground coffee ..."; }
    statemachine::Transition update() override { return {}; }
};

class StateReadyToBake: public statemachine::State {
public:
    StateReadyToBake() {
        this->attach<EventTurnFireOn>();
        this->attach<EventClean>();
    }
    std::string name() override { return "StateReadyToBake"; }
    std::string info() override { return "Ready to bake ..."; }
    statemachine::Transition update() override { return {}; }
};

class StateReadyToServe: public statemachine::State {
public:
    StateReadyToServe() {
        this->attach<EventServe>();
        this->attach<EventClean>();
    }
    std::string name() override { return "StateReadyToServe"; }
    std::string info() override { return "Ready to serve!"; }
    statemachine::Transition update() override { return {}; }
};

class StateDirty: public statemachine::State {
public:
    StateDirty() {
        this->attach<EventClean>();
    }
    std::string name() override { return "StateDirty"; }
    std::string info() override { return "Baker is dirty. Please wash before next usage."; }
    statemachine::Transition update() override { return {}; }
};

/* NonControllable Events */

class EventCoffeeReady: public statemachine::NonControllableEvent {
public:
    std::string name() override { return "CoffeeReady"; }
    statemachine::Transition execute() { return {new StateOn}; }
};

/* NonControllable States */

class StateBaking: public statemachine::State {
public:
    StateBaking():
        _timeout(5) {
        this->attach<EventTurnFireOff>();
    }

    std::string name() override {
        return "StateReadyToBake";
    }

    std::string info() override {
        std::string m = std::to_string(_timeout.count());
        return "Coffee ready in " + m + " minutes ...";
    }

    statemachine::Transition update() override {
        if(_timeout-- > 0) return {};
        else return EventCoffeeReady().execute();
    }

private:
    minutes _timeout;
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

} // moka
} // antoniocoratelli
