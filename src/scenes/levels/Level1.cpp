#include "Level1.hpp"

void Level1::resize()
{
    background.resize();
}

void Level1::update(unused double delta_time)
{
    background.update(delta_time);
}

void Level1::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(background, states);
}