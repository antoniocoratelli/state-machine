# state-machine

C++14 header-only library for implementing
[Finite-State Machines](https://en.wikipedia.org/wiki/Finite-state_machine).

The library provides the following four interfaces for building a state machine:
`State`s, `Event`s, `Transition`s, and the `StateMachine` itself.

- A `State` represents the current configuration of the *F.S.M.*,

## Usage

#### Build

Use a modern C++ compiler with support ot the C++14 standard.
The code was tested with `g++ 6.3.0 20170406`.

```
mkdir -p build && (cd build && cmake .. && make -j$(nproc))
```

## Examples

Unit tests are executed atomatically at the end of the build.

#### OnOffSwitch

#### TimedSwitch

#### Moka

## License

Released under *BSD 3-clause*. See [license file](LICENSE).
