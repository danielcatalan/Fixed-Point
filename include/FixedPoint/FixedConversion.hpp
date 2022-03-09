#ifndef FIXEDCONVERSION_HPP
#define FIXEDCONVERSION_HPP
#include <cstdint>

namespace fixedpoint
{
    union FloatUnion
    {
        float fvalue;
        struct{
            std::uint32_t mantissia : 23;
            std::uint32_t exponent : 8;
            std::uint32_t sign : 1;
        };

        inline std::int32_t GetExponent()
        {
            return exponent - 127;
        }
    };

    template <typename BaseIntType>
    BaseIntType float_to_fixed(const float x, std::size_t Q)
    {
        FloatUnion tmp{.fvalue=x};
        
        auto intvalue = tmp.mantissia | 0x00800000;
        intvalue = intvalue << tmp.GetExponent();
        return intvalue;
    }
}
// float fixed_to_float(const BaseIntType x)
// {

// }

#endif // #ifndef FIXEDCONVERSION_HPP