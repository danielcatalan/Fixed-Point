#ifndef FIXEDPOINT_HPP
#define FIXEDPOINT_HPP

#include <cstdint>
#include <cstdio>
#include <cmath>
#include "utils.hpp"

namespace fixedpoint
{
    /**
     * @brief Fixed Point class.
     *
     * @tparam BaseIntType base storage type of value.
     * @tparam Q Q-Formatparameter.
     */
    template <typename BaseIntType, std::size_t Q>
    class FixedPoint
    {
        static_assert(is_valid_integer_type<BaseIntType>::value, "Not a valid type to use with FixedPoint");
        using IntermediateType = typename get_intermediate_type<BaseIntType>::type;

        static constexpr BaseIntType K = 1 << (Q - 1);

        BaseIntType value;

    public:
        constexpr FixedPoint() : value(0) {}
        constexpr FixedPoint(BaseIntType num) : value(num << Q) {}
        constexpr FixedPoint(float num) : value(std::roundf(num * (1 << Q))) {}
        constexpr FixedPoint(double num) : value(std::round(num * (1 << Q))) {}

        constexpr float ToFloat() const
        {
            return this->value / (double)(1 << Q);
        }

        constexpr FixedPoint operator+(const FixedPoint &other) const
        {
            FixedPoint result;
            result.value = value + other.value;
            return result;
        }

        constexpr FixedPoint operator-(const FixedPoint &other) const
        {
            FixedPoint result;
            result.value = this->value - other.value;
            return result;
        }

        constexpr FixedPoint operator*(const FixedPoint &rhs) const
        {
            IntermediateType tmp = (IntermediateType)this->value * (IntermediateType)rhs.value;
            tmp += FixedPoint::K;

            FixedPoint result;
            result.value = FixedPoint::saturate(tmp >> Q);
            return result;
        }

        constexpr FixedPoint operator/(const FixedPoint &rhs) const
        {
            /* pre-multiply by the base (Upscale to Q16 so that the result will be in Q8 format) */
            IntermediateType temp = (IntermediateType)this->value << Q;
            /* Rounding: mid values are rounded up (down for negative values). */
            /* OR compare most significant bits i.e. if (((temp >> 31) & 1) == ((b >> 15) & 1)) */
            if ((temp >= 0 && rhs.value >= 0) || (temp < 0 && rhs.value < 0))
            {
                temp += rhs.value / 2; /* OR shift 1 bit i.e. temp += (b >> 1); */
            }
            else
            {
                temp -= rhs.value / 2; /* OR shift 1 bit i.e. temp -= (b >> 1); */
            }
            FixedPoint result;
            result.value = (BaseIntType)(temp / rhs.value);
            return result;
        }

    private:
        static constexpr BaseIntType saturate(IntermediateType x)
        {
            if (x > get_limits<BaseIntType>::max)
                return get_limits<BaseIntType>::max;
            else if (x < get_limits<BaseIntType>::min)
                return get_limits<BaseIntType>::min;
            else
                return (BaseIntType)x;
        }
    };

    template <std::size_t Q>
    using FixedPoint32 = FixedPoint<std::int32_t, Q>;

    template <std::size_t Q>
    using FixedPoint16 = FixedPoint<std::int16_t, Q>;
}

#endif // #ifndef FIXEDPOINT_HPP