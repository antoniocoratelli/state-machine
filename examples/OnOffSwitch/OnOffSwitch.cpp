#include <gtest/gtest.h>
#include "OnOffSwitch.h"

TEST(TestOnOffSwitch, main) {
    using namespace antoniocoratelli;

    // Initializing the switch: it's Off by default.
    OnOffSwitch on_off_switch;
    std::cout << on_off_switch.info() << std::endl;
    EXPECT_EQ(true, on_off_switch.in<StateOff>());
    EXPECT_EQ(false, on_off_switch.in<StateOn>());

    // This simple switch doesn't have non-controllable events in any state,
    // thus any call to the update() method will have no effect.
    on_off_switch.update();
    std::cout << on_off_switch.info() << std::endl;
    EXPECT_EQ(true, on_off_switch.in<StateOff>());
    EXPECT_EQ(false, on_off_switch.in<StateOn>());

    // Turning on the switch, we expect that the state changes to On
    on_off_switch.trigger<EventTurnOn>();
    std::cout << on_off_switch.info() << std::endl;
    EXPECT_EQ(false, on_off_switch.in<StateOff>());
    EXPECT_EQ(true, on_off_switch.in<StateOn>());

    // Trying to trigger an event that can't be triggered in this state
    EXPECT_THROW(on_off_switch.trigger<EventTurnOn>(), std::logic_error);

    // Turning off the switch, we expect that the state changes to Off
    on_off_switch.trigger<EventTurnOff>();
    std::cout << on_off_switch.info() << std::endl;
    EXPECT_EQ(true, on_off_switch.in<StateOff>());
    EXPECT_EQ(false, on_off_switch.in<StateOn>());

    // Trying to trigger an event that can't be triggered in this state
    EXPECT_THROW(on_off_switch.trigger<EventTurnOff>(), std::logic_error);
}
