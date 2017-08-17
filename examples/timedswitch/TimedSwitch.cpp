/*
 * Copyright 2017 Antonio Coratelli - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the BSD 3-Clause license.
 */
#include <gtest/gtest.h>
#include "TimedSwitch.h"

TEST(TestTimedSwitch, States) {
    using namespace antoniocoratelli::timedswitch;

    StateOn state_on;
    StateOff state_off;

    // Verifying which controllable events are enabled for each state.
    EXPECT_EQ(true,  state_on.triggers<EventTurnOff>());
    EXPECT_EQ(false, state_on.triggers<EventTurnOn>());
    EXPECT_EQ(true,  state_off.triggers<EventTurnOn>());
    EXPECT_EQ(false, state_off.triggers<EventTurnOff>());
}

TEST(TestTimedSwitch, Events) {
    using namespace antoniocoratelli::timedswitch;

    EventTurnOn turn_on;
    EventTurnOff turn_off;
    EventTimeout timeout;

    // The events aren't self-transitions.
    EXPECT_EQ(true, turn_on.execute().operator bool());
    EXPECT_EQ(true, turn_off.execute().operator bool());
    EXPECT_EQ(true, timeout.execute().operator bool());
}

TEST(TestTimedSwitch, StateMachine) {
    using namespace antoniocoratelli::timedswitch;

    // Initializing the switch: it's Off by default.
    TimedSwitch timed_switch;
    std::cout << timed_switch.info() << std::endl;
    EXPECT_EQ(true, timed_switch.in<StateOff>());
    EXPECT_EQ(false, timed_switch.in<StateOn>());

    // Turning on the switch, we expect that the state changes to On.
    timed_switch.trigger<EventTurnOn>();
    std::cout << timed_switch.info() << std::endl;
    EXPECT_EQ(false, timed_switch.in<StateOff>());
    EXPECT_EQ(true, timed_switch.in<StateOn>());

    // We wait until the timer turns off the switch.
    while(not timed_switch.update())
        std::cout << timed_switch.info() << std::endl;
    EXPECT_EQ(true, timed_switch.in<StateOff>());
    EXPECT_EQ(false, timed_switch.in<StateOn>());

    // Trying to trigger an event that can't be triggered in this state.
    EXPECT_THROW(timed_switch.trigger<EventTurnOff>(), std::logic_error);

    // We turn on again the switch, but this time we turn it off manually
    // before the timeout.
    EXPECT_NO_THROW(timed_switch.trigger<EventTurnOn>());
    std::cout << timed_switch.info() << std::endl;
    EXPECT_EQ(false, timed_switch.update());
    std::cout << timed_switch.info() << std::endl;
    EXPECT_EQ(false, timed_switch.update());
    std::cout << timed_switch.info() << std::endl;
    EXPECT_NO_THROW(timed_switch.trigger<EventTurnOff>());
    std::cout << timed_switch.info() << std::endl;
    EXPECT_EQ(true, timed_switch.in<StateOff>());
    EXPECT_EQ(false, timed_switch.in<StateOn>());

    // Turning On the switch, we expect that the state changes to On.
    timed_switch.trigger<EventTurnOn>();
    std::cout << timed_switch.info() << std::endl;
    EXPECT_EQ(false, timed_switch.in<StateOff>());
    EXPECT_EQ(true, timed_switch.in<StateOn>());

    // Trying to trigger an event that can't be triggered in this state.
    EXPECT_THROW(timed_switch.trigger<EventTurnOn>(), std::logic_error);
}
