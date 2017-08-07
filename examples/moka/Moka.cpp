#include <gtest/gtest.h>
#include "Moka.h"

TEST(TestMoka, States) {
    using namespace antoniocoratelli::moka;

    // Verifying which controllable events are enabled for each state.
    EXPECT_EQ(true,  StateIdle().triggers<EventFillWater>());
    EXPECT_EQ(false, StateIdle().triggers<EventClean>());
    EXPECT_EQ(false, StateWaitingForGroundCoffee().triggers<EventFillWater>());
    EXPECT_EQ(true,  StateWaitingForGroundCoffee().triggers<EventClean>());
    EXPECT_EQ(true,  StateReadyToBrew().triggers<EventClean>());
    EXPECT_EQ(true,  StateReadyToBrew().triggers<EventTurnFireOn>());
    EXPECT_EQ(false, StateReadyToBrew().triggers<EventTurnFireOff>());
    EXPECT_EQ(true,  StateBrewing().triggers<EventTurnFireOff>());
    EXPECT_EQ(false, StateBrewing().triggers<EventTurnFireOn>());
    EXPECT_EQ(true,  StateDirty().triggers<EventClean>());
    EXPECT_EQ(false, StateDirty().triggers<EventServe>());
    EXPECT_EQ(true,  StateReadyToServe().triggers<EventServe>());
    EXPECT_EQ(false, StateReadyToServe().triggers<EventFillWater>());
}

