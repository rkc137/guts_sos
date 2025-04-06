#pragma once

#include <SFML/Graphics.hpp>

#include <type_traits>
#include <concepts>

template <typename T>
concept WindowWrapTC = requires {
    { T::get_window() } -> std::same_as<sf::RenderWindow&>; 
};

class DefaultWindowWrap
{
public:
    static void set_window_wrap_ptr(sf::RenderWindow *window) { win = window; }
protected:
    static sf::RenderWindow& get_window() { return *win; }
private:
    inline static sf::RenderWindow *win = nullptr; 
};

using namespace std::literals::string_literals;