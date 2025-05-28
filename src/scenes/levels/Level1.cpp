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
        state += shaker.is_done();
    break;
    case 1:
        one_time([&]{
            draws = { &commander };
            commander.set_phease("");
        });
        commander.update(delta_time);
        state += commander.is_end_of_phrase();
    break;
    case 2:
        one_time([&]{
            draws = { &troop };
            troop.set_phease("");
        });
        troop.update(delta_time);
        state += troop.is_end_of_phrase();
    break;
    case 3:
        one_time([&]{
            draws = { &commander };
            commander.set_phease("NOW NOW NOW");
        });
        commander.update(delta_time);
        state += commander.is_end_of_phrase();
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