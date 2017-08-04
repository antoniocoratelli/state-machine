#ifndef ANTONIOCORATELLI_STATE_H
#define ANTONIOCORATELLI_STATE_H

#include <memory>

namespace antoniocoratelli
{
    // Forward declaration needed for iterate() return value
    class Transition;

    class State
    {
    public:
        State() {}

        virtual ~State() {}

        virtual Transition update() = 0;

        virtual std::string name() = 0;

        virtual std::string info() = 0;

        typedef std::unique_ptr<State> uptr_t;
    };
}

#endif
