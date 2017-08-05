#pragma once
#include <memory>
#include <set>
#include <string>
#include <typeindex>
#include "Event.h"
#include "Transition.h"

namespace antoniocoratelli {
namespace statemachine {

class ControllableEvent;
class NonControllableEvent;

class State {
public:
    typedef std::unique_ptr<State> uptr_t;

    State() {}

    virtual ~State() {}

    virtual Transition update() = 0;

    virtual std::string name() = 0;

    virtual std::string info() = 0;

    template<class controllable_event_t> bool triggers() const;

protected:
   template<class controllable_event_t> void attach();

private:
    std::set<std::type_index> _allowed_controllable_events;
};

template<class controllable_event_t> inline void State::attach() {
    static_assert(std::is_base_of<ControllableEvent, controllable_event_t>::value);
    std::type_index event_type(typeid(controllable_event_t));
    _allowed_controllable_events.insert(event_type);
}

template<class controllable_event_t> inline bool State::triggers() const {
    static_assert(std::is_base_of<ControllableEvent, controllable_event_t>::value);
    std::type_index event_type(typeid(controllable_event_t));
    return _allowed_controllable_events.count(event_type) > 0;
}

} // statemachine
} // antoniocoratelli

