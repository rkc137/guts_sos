#include "WindowWrap.hpp"

void DefaultWindowWrap::set_window_wrap_ptr(sf::RenderWindow *window)
{
    win = window;
}

void DefaultWindowWrap::check_window()
{
    if(!win)
        throw std::runtime_error("window wrapper lost window");
}

sf::RenderWindow& DefaultWindowWrap::get_window()
{
    return *win;
}
