# state-machine [![Build Status][build-img]][build-link]

C++14 header-only library for implementing
[Finite-State Machines](https://en.wikipedia.org/wiki/Finite-state_machine).

The library provides the following three interfaces for building a state machine:
`State`, `Event` and the `StateMachine` itself.

- `State`s represent the possible configurations of a `StateMachine`.

- `Event`s represent the possible transitions between `State`s.

- Each `Event` defines the destination `State` that the `StateMachine`
  reaches if the `Event` itself is triggered.

- `Event`s can be `Controllable` and `NonControllable`:

  - `Controllable` events are executed by the user;

  - `NonControllable` events are events that are not under the direct control
    of the user (for instance failures or timeouts).

- Each `State` declares the `ControllableEvent`s that are available using the
  `State::attach<ControllableEvent>()` method, and defines the logic for triggering
  `NonControllableEvents` in the `State::update()` method.

## Build

Use a modern C++ compiler with support ot the C++14 standard.
The code was tested with `g++ 6.3.0 20170406`.

Run in the project folder:

```
mkdir -p build && (cd build && cmake .. && make -j$(nproc))
```

Unit tests for the examples are executed automatically at the end of the build.

## Examples

#### OnOffSwitch

#### TimedSwitch

#### Moka

## License

Released under *BSD 3-clause*. See [license file](LICENSE).


[build-img]: https://travis-ci.org/antoniocoratelli/state-machine.svg?branch=master
[build-link]: https://travis-ci.org/antoniocoratelli/state-machine
