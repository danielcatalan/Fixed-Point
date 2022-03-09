#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstdint>

template<typename Base>
struct is_valid_integer_type{static constexpr auto value = false;};

template<>
struct is_valid_integer_type<std::int32_t>{static constexpr auto value = true;};

template<>
struct is_valid_integer_type<std::int16_t>{static constexpr auto value = true;};


template<typename Base>
struct get_intermediate_type;

template<>
struct get_intermediate_type<std::int32_t>{using type = std::int64_t;};

template<>
struct get_intermediate_type<std::int16_t>{using type = std::int32_t;};


template<typename Base>
struct get_limits;

template<>
struct get_limits<std::int32_t>{
    static constexpr auto max = INT32_MAX;
    static constexpr auto min = INT32_MIN;};

template<>
struct get_limits<std::int16_t>{
    static constexpr auto max = INT16_MAX;
    static constexpr auto min = INT16_MIN;};



#endif // #ifndef UTILS_HPP