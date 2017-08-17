/*
 * Copyright 2017 Antonio Coratelli - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the BSD 3-Clause license.
 */
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

TEST(TestMoka, NormalUsage) {
    using namespace antoniocoratelli::moka;

    // Initializing the moka: it's Idle by default.
    Moka moka;
    std::cout << moka.info() << std::endl;
    EXPECT_EQ(true, moka.in<StateIdle>());

    // Filling water.
    EXPECT_NO_THROW(moka.trigger<EventFillWater>());
    std::cout << moka.info() << std::endl;
    EXPECT_EQ(true, moka.in<StateWaitingForGroundCoffee>());

    // Adding ground coffee.
    EXPECT_NO_THROW(moka.trigger<EventPutGroundCoffee>());
    std::cout << moka.info() << std::endl;
    EXPECT_EQ(true, moka.in<StateReadyToBrew>());

    // Turning fire on.
    EXPECT_NO_THROW(moka.trigger<EventTurnFireOn>());
    std::cout << moka.info() << std::endl;
    EXPECT_EQ(true, moka.in<StateBrewing>());

    // Waiting for it to finish.
    while (not moka.update())
        std::cout << moka.info() << std::endl;
    EXPECT_EQ(true, moka.in<StateReadyToServe>());

    // Serving.
    EXPECT_NO_THROW(moka.trigger<EventServe>());
    std::cout << moka.info() << std::endl;
    EXPECT_EQ(true, moka.in<StateDirty>());

    // Cleaning.
    EXPECT_NO_THROW(moka.trigger<EventClean>());
    std::cout << moka.info() << std::endl;
    EXPECT_EQ(true, moka.in<StateIdle>());
}
