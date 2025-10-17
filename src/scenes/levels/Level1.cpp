#include "Level1.hpp"

Level1::Level1()
{
    incoming.play();
}

void Level1::resize()
{
    background.resize();
    commander.resize();
    troop.resize();
    shaker.resize(); 
}

void Level1::update(unused double delta_time)
{
    background.update(delta_time);
    switch(state)
    {
    case 0:
        shaker.update(delta_time);
        if(shaker.is_done())
        {
            state++;
            draws = { &troop };
        }
    break;
    case 1:
        troop.update(delta_time);
        if(troop.is_end_of_speech())
        {
            state++;
            draws = { &commander };
        }
    break;
    case 2:
        commander.update(delta_time);
        state += commander.is_end_of_speech();
    break;
    default:
    break;
    }
}

void Level1::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(background, states);
    for(auto &d : draws)
        target.draw(*d, states);
}