#pragma once

#include <SFML/System.hpp>

#include <type_traits>

namespace anim
{

/// @brief interpolates between two values over a time range
/// @tparam FuncT The type of animation function, that returns a floating point value
/// @param range start and end of values for animantion
/// @param elapsed_time The time that has passed since the starting point
/// @param end_time duration of animation
/// @return interpolated value between 0 and 1
template <typename FuncT, typename T = float>
requires std::is_invocable_r_v<T, FuncT, T> && std::is_floating_point_v<T>
T interpolate(
    const std::pair<T, T> &range,
    const sf::Time &elapsed_time,
    const sf::Time &end_time)
{
    static constinit FuncT func;
    auto &[from, to] = range;
    return from + (to - from) * func(std::clamp(
        elapsed_time.asSeconds() / end_time.asSeconds(),
        T{0}, T{1}
    ));
}

/// @brief makes avery change per frame
/// @param x value between 0 and 1
/// @return y value for f(x) = 1 - (1 - x^3)
using ease_out_cubic = decltype([](float x) -> float {
    return 1 - std::pow(1 - x, 3);
});

struct TextureMetaInfo
{
    sf::Vector2i frame_size;
    std::vector<int> animations_lengths;
};
struct Texture : public sf::Texture, public TextureMetaInfo {};
//TextureSetup(Texture &texture, TextureMetaInfo &&info)
//    static_cast<TextureMetaInfo&>(texture) = std::move(info);


} // anim
