#include "Opening.hpp"

void Opening::resize()
{
    auto ws = get_window().getSize();
    
    curtain.resize();
    author.set_char_size(ws.y / 10); 
    author.setPosition({ws.x / 2.f, ws.y / 3.f});
    
    made_with.set_char_size(ws.y / 12); 
    made_with.setPosition({ws.x / 2.f, ws.y / 3.f * 2});
}

void Opening::update(double delta_time)
{
    curtain.update(delta_time);
}

void Opening::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(author, states);
    target.draw(made_with, states);
    target.draw(curtain, states);
}
