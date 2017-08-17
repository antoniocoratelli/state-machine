/*
 * Copyright 2017 Antonio Coratelli - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the BSD 3-Clause license.
 */
#pragma once
#include <chrono>
#include <antoniocoratelli/statemachine/StateMachine.h>

namespace antoniocoratelli {
namespace moka {

using std::chrono::minutes;

/* Controllable Events forward declarations */

class EventFillWater;
class EventPutGroundCoffee;
class EventTurnFireOn;
class EventTurnFireOff;
class EventServe;
class EventClean;

/* Controllable States */

class StateIdle: public statemachine::State {
public:
    StateIdle() {
        this->attach<EventFillWater>();
    }
    std::string name() override { return "Idle"; }
    std::string info() override { return "Clean and ready to prepare another coffee."; }
    statemachine::Transition update() override { return {}; }
};

class StateWaitingForGroundCoffee: public statemachine::State {
public:
    StateWaitingForGroundCoffee() {
        this->attach<EventPutGroundCoffee>();
        this->attach<EventClean>();
    }
    std::string name() override { return "ReadyForGroundCoffee"; }
    std::string info() override { return "Waiting for ground coffee ..."; }
    statemachine::Transition update() override { return {}; }
};

class StateReadyToBrew: public statemachine::State {
public:
    StateReadyToBrew() {
        this->attach<EventTurnFireOn>();
        this->attach<EventClean>();
    }
    std::string name() override { return "ReadyToBrew"; }
    std::string info() override { return "Ready to brew ..."; }
    statemachine::Transition update() override { return {}; }
};

class StateReadyToServe: public statemachine::State {
public:
    StateReadyToServe() {
        this->attach<EventServe>();
        this->attach<EventClean>();
    }
    std::string name() override { return "ReadyToServe"; }
    std::string info() override { return "Ready to serve!"; }
    statemachine::Transition update() override { return {}; }
};

class StateDirty: public statemachine::State {
public:
    StateDirty() {
        this->attach<EventClean>();
    }
    std::string name() override { return "Dirty"; }
    std::string info() override { return "Moka is dirty. Please wash before next usage."; }
    statemachine::Transition update() override { return {}; }
};

/* NonControllable Events */

class EventCoffeeReady: public statemachine::NonControllableEvent {
public:
    std::string name() override { return "CoffeeReady"; }
    statemachine::Transition execute() { return {new StateReadyToServe}; }
};

/* NonControllable States */

class StateBrewing: public statemachine::State {
public:
    StateBrewing():
        _timeout(5) {
        this->attach<EventTurnFireOff>();
    }

    std::string name() override {
        return "Brewing";
    }

    std::string info() override {
        std::string m = std::to_string(_timeout.count());
        return "Coffee ready in " + m + " minutes ...";
    }

    statemachine::Transition update() override {
        if (_timeout-- > minutes(0)) return {};
        else return EventCoffeeReady().execute();
    }

private:
    minutes _timeout;
};

/* Controllable Events */

class EventFillWater: public statemachine::ControllableEvent {
public:
    std::string name() override { return "PutWater"; }
    statemachine::Transition execute() { return {new StateWaitingForGroundCoffee}; }
};

class EventPutGroundCoffee: public statemachine::ControllableEvent {
public:
    std::string name() override { return "PutGroundCoffee"; }
    statemachine::Transition execute() { return {new StateReadyToBrew}; }
};

class EventTurnFireOn: public statemachine::ControllableEvent {
public:
    std::string name() override { return "TurnFireOn"; }
    statemachine::Transition execute() { return {new StateBrewing}; }
};

class EventTurnFireOff: public statemachine::ControllableEvent {
public:
    std::string name() override { return "TurnFireOff"; }
    statemachine::Transition execute() { return {new StateDirty}; }
};

class EventServe: public statemachine::ControllableEvent {
public:
    std::string name() override { return "Serve"; }
    statemachine::Transition execute() { return {new StateDirty}; }
};

class EventClean: public statemachine::ControllableEvent {
public:
    std::string name() override { return "Clean"; }
    statemachine::Transition execute() { return {new StateIdle}; }
};

/* State Machine */

class Moka: public statemachine::StateMachine {
public:
    Moka(): StateMachine(std::make_unique<StateIdle>()) {}
    std::string name() const override { return "Moka::" + _current_state->name(); }
    std::string info() const override { return "{" + name() + "} " + _current_state->info(); }
};

}  // namespace moka
}  // namespace antoniocoratelli
