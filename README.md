# state-machine

C++14 header-only library for implementing
[Finite-State Machines](https://en.wikipedia.org/wiki/Finite-state_machine).

[![Build Status][build-img]][build-link]
[![Documentation][doc-img]][doc-link]
[![License][license-img]][license-link]


> This project is hosted on [GitLab][gl-link] and mirrored on [GitHub][gh-link].
> Please open *Issues* and *Merge Requests* on GitLab.

[gl-link]: https://gitlab.com/antoniocoratelli/state-machine
[gh-link]: https://github.com/antoniocoratelli/state-machine

## Interface

The library provides the following three interfaces for building a state
 machine: `State`, `Event` and the `StateMachine` itself.

- `State`s represent the possible configurations of a `StateMachine`.

- `Event`s represent the possible transitions between `State`s.

- Each `Event` defines the destination `State` that the `StateMachine`
  reaches if the `Event` itself is triggered.

- `Event`s can be `Controllable` and `NonControllable`:

  - `Controllable` events are executed by the user;

  - `NonControllable` events are events that are not under the direct control
    of the user (for instance failures or timeouts).

- Each `State` declares the `ControllableEvent`s that are available using the
  `State::attach<ControllableEvent>()` method, and defines the logic for
  triggering `NonControllableEvents` in the `State::update()` method.

## Build

Use a modern C++ compiler with support ot the C++14 standard.
Code was developed using `g++ 6.3.0 20170406`.

Run in the project folder:

```
mkdir -p build && (cd build && cmake .. && make -j$(nproc))
```

## Examples

In order to validate and demonstrate the usage of the library, three examples
have been developed: a simple On/Off switch, an On/Off switch with an
automatic reset timer, and a [Moka][moka-img] coffee brewer.

Unit tests for these examples are executed automatically at the end of the
build.

Controllable events and states are showed in black, while NonControllable
events and states are shown in red.

#### OnOffSwitch ([implementation][example-code-onoffswitch], [tests][example-test-onoffswitch])

![OnOffSwitch][example-img-onoffswitch]

#### TimedSwitch ([implementation][example-code-timedswitch], [tests][example-test-timedswitch])

![TimedSwitch][example-img-timedswitch]

#### Moka ([implementation][example-code-moka], [tests][example-test-moka])

![Moka][example-img-moka]


[build-img]: https://gitlab.com/antoniocoratelli/state-machine/badges/master/build.svg
[build-link]: https://gitlab.com/antoniocoratelli/state-machine/commits/master

[doc-img]: https://img.shields.io/badge/doxy-available-brightgreen.svg?style=flat
[doc-link]: https://antoniocoratelli.gitlab.io/state-machine/annotated.html

[license-img]: https://img.shields.io/badge/license-BSD-blue.svg?style=flat
[license-link]: LICENSE

[example-img-onoffswitch]: doc/examples/onoffswitch.jpg
[example-img-timedswitch]: doc/examples/timedswitch.jpg
[example-img-moka]: doc/examples/moka.jpg

[example-code-onoffswitch]: examples/onoffswitch/OnOffSwitch.h
[example-code-timedswitch]: examples/timedswitch/TimedSwitch.h
[example-code-moka]: examples/moka/Moka.h

[example-test-onoffswitch]: examples/onoffswitch/OnOffSwitch.cpp
[example-test-timedswitch]: examples/timedswitch/TimedSwitch.cpp
[example-test-moka]: examples/moka/Moka.cpp

[moka-img]: https://upload.wikimedia.org/wikipedia/commons/thumb/d/de/Moka2.jpg/855px-Moka2.jpg
