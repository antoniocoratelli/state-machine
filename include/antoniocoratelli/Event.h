#ifndef ANTONIOCORATELLI_EVENT_H
#define ANTONIOCORATELLI_EVENT_H

#include <string>
#include "Transition.h"

namespace antoniocoratelli {

class Event {
    virtual Transition execute() = 0;
    virtual std::string name() = 0;
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

#endif
