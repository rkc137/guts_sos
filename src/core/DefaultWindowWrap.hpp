#pragma once

#include <SFML/Graphics.hpp>

class DefaultWindowWrap
{
public:
    static void set_window_wrap_ptr(sf::RenderWindow *window) { win = window; }
protected:
    static sf::RenderWindow& get_window() { return *win; }
private:
    inline static sf::RenderWindow *win = nullptr; 
};