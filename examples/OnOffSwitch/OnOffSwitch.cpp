#include <gtest/gtest.h>
#include "OnOffSwitch.h"

TEST(TestOnOffSwitch, main) {
    using namespace antoniocoratelli;

    OnOffSwitch on_off_switch;

    std::cout << on_off_switch.info() << std::endl;
    EXPECT_EQ(true, on_off_switch.in<StateOff>());
    EXPECT_EQ(false, on_off_switch.in<StateOn>());

    on_off_switch.update();

    std::cout << on_off_switch.info() << std::endl;
    EXPECT_EQ(true, on_off_switch.in<StateOff>());
    EXPECT_EQ(false, on_off_switch.in<StateOn>());

    on_off_switch.trigger<EventTurnOn>();

    std::cout << on_off_switch.info() << std::endl;
    EXPECT_EQ(false, on_off_switch.in<StateOff>());
    EXPECT_EQ(true, on_off_switch.in<StateOn>());
}
