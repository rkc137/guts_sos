#pragma once

#include <SFML/Graphics.hpp>

#include <type_traits>
#include <concepts>

#include "Utils.hpp"

template <typename T>
concept WindowWrapTC = requires {
    { T::get_window() } -> std::same_as<sf::RenderWindow&>; 
};

class DefaultWindowWrap
{
public:
    static void set_window_wrap_ptr(sf::RenderWindow *window);
    static void check_window();
protected:
    static sf::RenderWindow& get_window();
    template <typename T = unsigned int>
    requires (std::is_arithmetic_v<T>)
    static sf::Vector2<T> get_wsize()
    {
        return static_cast<sf::Vector2<T>>(get_window().getSize());
    }
private:
    inline static sf::RenderWindow *win = nullptr; 
};