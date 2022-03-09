#include <gtest/gtest.h>
#include "FixedPoint/FixedConversion.hpp"
#include <cmath>


class Int32Conversion :
    public testing::TestWithParam<float> {};

TEST_P(Int32Conversion, Q23_f2i)
{
    auto fval = GetParam();

    auto expected = (std::int32_t) std::roundf(fval * (1<<23));
    
    auto x = fixedpoint::float_to_fixed<std::int32_t>(fval, 23);
    EXPECT_EQ(expected, x);    
}

INSTANTIATE_TEST_SUITE_P(SimpleFloats2Int,
                         Int32Conversion,
                         testing::Values(
                            1.0f,1.00000011921f, 1.5f, 1.99999988079f, // test 1.0 <= f < 2.0
                            2.0f, 2.00000023842f, 3.0f, 3.99999976158f // test 2.0 <= f < 4.0
                         )); 