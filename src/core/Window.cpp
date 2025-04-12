#include "Window.hpp"

Window::Window() : sf::RenderWindow(
    default_video_mode,
    res::app_name,
    sf::State::Windowed)
{
    setFramerateLimit(60);
    if(!res::is_loaded())
        throw std::runtime_error("resources was not loaded");
    setTitle(res::app_name);
    setIcon(res::default_texture.copyToImage());
    DefaultWindowWrap::set_window_wrap_ptr(this);
}

void Window::change_fullscreen()
{
    if(!is_full_screen)
        create(
            sf::VideoMode::getFullscreenModes().front(),
            res::app_name,
            sf::State::Fullscreen
        );
    else
        create(
            default_video_mode,
            res::app_name,
            sf::State::Windowed
        );
    is_full_screen = !is_full_screen;
}