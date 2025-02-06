#include <gtest/gtest.h>

#include "Test.h"

TEST(MathTest, Addition) {
    EXPECT_EQ(ppp::Test::add(2, 3), 5);
    EXPECT_EQ(ppp::Test::add(-1, 1), 0);
    EXPECT_EQ(ppp::Test::add(0, 0), 0);
    EXPECT_EQ(ppp::Test::add(-2, -3), -5);
}
