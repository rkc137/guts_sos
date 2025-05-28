#pragma once

#include <SFML/Graphics.hpp>
#include <type_traits>
#include <concepts>

#ifndef DEBUG
#include <cassert>
#include "logger/Logger.hpp"
#endif

#define unused [[maybe_unused]]

#define one_time(f) [&](){ \
    static bool first = true; \
    if(first) {\
        first = false; \
        f(); \
    } \
}()

template <typename T>
constexpr sf::Vector2<T> operator/(sf::Vector2<T> a, sf::Vector2<T> b) noexcept
{
    return {
        a.x / b.x,
        a.y / b.y
    };
}

template <typename T>
constexpr sf::Vector2<T> operator*(sf::Vector2<T> a, sf::Vector2<T> b) noexcept
{
    return {
        a.x * b.x,
        a.y * b.y
    };
}

template <typename T, typename U> 
requires (std::is_arithmetic_v<U>) 
constexpr sf::Vector2<T> operator/(sf::Vector2<T> a, U b) noexcept
{
    return {
        a.x / b,
        a.y / b
    };
}

template <typename T, typename U> 
requires (std::is_arithmetic_v<U>) 
constexpr sf::Vector2<T> operator*(sf::Vector2<T> a, U b) noexcept
{
    return {
        a.x * b,
        a.y * b
    };
}