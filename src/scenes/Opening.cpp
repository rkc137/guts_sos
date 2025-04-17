#include "Opening.hpp"

void Opening::resize()
{
    auto ws = get_window().getSize();
    
    author.set_char_size(ws.y / 10); 
    author.setPosition({ws.x / 2.f, ws.y / 3.f});
    
    made_with.set_char_size(ws.y / 12); 
    made_with.setPosition({ws.x / 2.f, ws.y / 3.f * 2});
}

void Opening::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    target.draw(author, states);
    target.draw(made_with, states);
}

void Opening::update(unused double delta_time)
{
    auto time = clock.getElapsedTime();
    
    static float alpha = 0;

    static bool show_up = false;
    static bool showed = false;
    if(!show_up && time < duration)
    {
        alpha = time / duration * 255.f;
        show_up = alpha > 254;
        if(show_up) clock.restart();
    } 
    else if(time > (duration + duration))
    {
        showed = true;
        clock.restart();
    }
    else if(showed)
    {
        alpha = 255.f - (time / duration * 255.f);
        if(alpha < 1)
            quit();
    }
    author.set_fill_color({255, 255, 255, static_cast<uint8_t>(alpha)});
    made_with.set_fill_color({255, 255, 255, static_cast<uint8_t>(alpha)});
}
