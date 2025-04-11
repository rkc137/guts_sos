#pragma once

#include <SFML/Graphics.hpp>

#include "WindowWrap.hpp"
#include "../res/res.hpp"

class Window : public sf::RenderWindow
{
public:
    Window();
    void change_fullscreen();
private:
    sf::VideoMode video_mode{{1280, 720}};
    bool is_full_screen = false;
};
