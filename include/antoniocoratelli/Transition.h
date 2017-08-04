#ifndef ANTONIOCORATELLI_TRANSITION_H
#define ANTONIOCORATELLI_TRANSITION_H

#include <experimental/optional>
#include "State.h"

namespace antoniocoratelli
{
    /**
     * Transition provides a simple interface to specify
     */
    class Transition:
        private std::experimental::optional<State::uptr_t>
    {
    public:
        inline bool emitted() const { return bool(); }

        inline State::uptr_t destination() { return std::move(value()); }
    };
}

#endif
