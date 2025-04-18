#include "Curtain.hpp"

Curtain::Curtain(sf::Time duration, bool is_quiting_on_time) 
    : duration(duration), is_quiting_on_time(is_quiting_on_time)
{}

void Curtain::resize()
{
    shape.setSize(sf::Vector2f(get_window().getSize()));
}

void Curtain::update(unused double delta_time)
{
    auto time = clock.getElapsedTime();
    static float alpha = 0;
    static bool show_up = false;
    static bool showed = false;
    if(!show_up && time < duration)
    {
        alpha = 255.f - (time / duration * 255.f);
        show_up = alpha < 1;
        if(show_up)
            clock.restart();
    } 
    else if(should_quit || (time > (duration + duration) && is_quiting_on_time))
    {
        showed = true;
        clock.restart();
    }
    else if(showed)
    {
        alpha = time / duration * 255.f;
        if(alpha > 254) 
            quit();
    }
    shape.setFillColor({0, 0, 0, static_cast<uint8_t>(alpha)});
}

void Curtain::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(shape, states);
}
