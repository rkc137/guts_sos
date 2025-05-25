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
}

void Level1::update(unused double delta_time)
{
    if(state > 1)
        background.update(delta_time);
    switch(state)
    {
    case 0:
        state += incoming.getStatus() == sf::Sound::Status::Stopped;
        //сюда
        break;
    case 1:
        if(commander.is_end_of_phrase())
        {
            state++;
            commander.set_phease("NOW NOW NOW");
        }
        commander.update(delta_time);
        break;
    case 2:
        if(troop.is_end_of_phrase());
            state++;
        troop.update(delta_time);
        break;
    case 3:
        state += commander.is_end_of_phrase();
        commander.update(delta_time);
        break;
    default:
        break;
    }
}

void Level1::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(background, states);
    switch(state)
    {
    case 0:
        target.draw(commander, states);
        break;
    case 1:
        target.draw(troop, states);
        break;
    case 2: case 3:
        target.draw(commander, states);
    default:
        break;
    }
}