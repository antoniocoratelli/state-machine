#pragma once
#include <string>
#include "Transition.h"

namespace antoniocoratelli {
namespace statemachine {

/**
 * Base interface for all types of Events.
 * @see ControllableEvent
 * @see NonControllableEvent
 */
class Event {
public:
    virtual Transition execute() = 0;
    virtual std::string name() = 0;
    virtual ~Event() {}
};

/**
 * Base class for all the events that can be controlled by the user
 * of the state machine.
 */
class ControllableEvent: public Event {
public:
    virtual ~ControllableEvent() {}
};

/**
 * Base class for all the events that are out of the control of the
 * user of the state machine. For example: timers, failures.
 */
class NonControllableEvent: public Event {
public:
    virtual ~NonControllableEvent() {}
};

} // statemachine
} // antoniocoratelli
