# state-machine

C++14 header-only library for implementing
[Finite-State Machines](https://en.wikipedia.org/wiki/Finite-state_machine).

The library provides the following three interfaces for building a state machine:
`State`, `Event` and the `StateMachine` itself.

- A `State` represents the current configuration of the *F.S.M.*.

- `Event`s represent the possible transitions between `State`s.
  Each `Event` defines the destination `State` that the `StateMachine`
  reaches if the `Event` itself is triggered.

- `Event`s can be `Controllable` and `NonControllable`:

  - `Controllable` events are executed by the user;

  - `NonControllable` events are events that are not under direct control of the user
    (such events can be for instance failures or timeouts).

- Each `State` declares the `ControllableEvent`s that are available using the
  `State::attach<Event>()` method, and defines the logic for handling
  `NonControllableEvents` in the `State::update()` method.

## Build

Use a modern C++ compiler with support ot the C++14 standard.
The code was tested with `g++ 6.3.0 20170406`.

```
mkdir -p build && (cd build && cmake .. && make -j$(nproc))
```

Example tests are executed automatically at the end of the build.

## Examples

#### OnOffSwitch

#### TimedSwitch

#### Moka

## License

Released under *BSD 3-clause*. See [license file](LICENSE).
