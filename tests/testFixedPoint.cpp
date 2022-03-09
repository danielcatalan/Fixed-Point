#include <gtest/gtest.h>
#include "FixedPoint/FixedPoint.hpp"

TEST(Base, ToFloat)
{
    const auto x = fixedpoint::FixedPoint32<16>(1.5);
    EXPECT_FLOAT_EQ(1.5, x.ToFloat());

    auto y = fixedpoint::FixedPoint32<26>(1.0f/3.0f);
    // EXPECT_NEAR(1.0/3.0, y.ToFloat(), 0.0001);
    EXPECT_EQ(1.0f/3.0f, y.ToFloat());
}

TEST(Arithmatic, Add)
{
    const auto x = fixedpoint::FixedPoint16<8>(3.25);
    const auto y = fixedpoint::FixedPoint16<8>(1.5);

    auto z = x + y;
    EXPECT_EQ(4.75, z.ToFloat());
}

TEST(Arithmatic, Subtract)
{
    auto x = fixedpoint::FixedPoint32<16>(7);
    auto y = fixedpoint::FixedPoint32<16>(1.5);

    auto z = x - y;
    EXPECT_EQ(5.5, z.ToFloat());
}

TEST(Arithmatic, Multiply)
{
    auto x = fixedpoint::FixedPoint32<16>(6);
    auto y = fixedpoint::FixedPoint32<16>(0.25);

    auto z = x * y;
    EXPECT_EQ(1.5, z.ToFloat());
}

TEST(Arithmatic, Divide)
{
    const auto x = fixedpoint::FixedPoint32<16>(6);
    const auto y = fixedpoint::FixedPoint32<16>(4);

    auto z = x / y;
    EXPECT_EQ(1.5, z.ToFloat());
}