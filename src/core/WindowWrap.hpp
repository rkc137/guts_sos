#pragma once

#include <SFML/Graphics.hpp>

#include <type_traits>
#include <concepts>
#include <cassert>

#include "logger/Logger.hpp"

#define unused [[maybe_unused]]

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
private:
    inline static sf::RenderWindow *win = nullptr; 
};