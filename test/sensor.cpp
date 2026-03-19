#include <gtest/gtest.h>
#include <sensor.h>

// Test case 1: LLR1- Frequency is 0 or negative (should return FALSE)
TEST(sensorIntialization, sensorIntialization_InvalidFrequency_Test)
{
    EXPECT_FALSE(sensorIntialization(0));
    EXPECT_FALSE(sensorIntialization(-100));
}

// tEST CASE 2: LLR2 - Frequency greater than zero
TEST(sensorIntialization, sensorIntialization_validFrequency_Test)
{
    EXPECT_TRUE(sensorIntialization(10000));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

