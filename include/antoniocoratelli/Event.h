#pragma once
#include <string>
#include "Transition.h"

namespace antoniocoratelli {

class Event {
public:
    virtual Transition execute() = 0;
    virtual std::string name() = 0;
    virtual ~Event() {}
};

class ControllableEvent: public Event {
public:
    virtual ~ControllableEvent() {}
};

class NonControllableEvent: public Event {
public:
    virtual ~NonControllableEvent() {}
};

} // antoniocoratelli
