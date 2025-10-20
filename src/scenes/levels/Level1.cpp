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
    blocknote.setPosition({0, get_wsize<float>().y});
    blocknote.setScale(res::get_scale(get_wsize<float>()));
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
        if(commander.is_end_of_speech())
        {
            state++;
            draws = { &blocknote };
            auto [pos, size] = blocknote.get_global_bounds();
            blocknote.setPosition({-size.x, get_wsize<float>().y});
            blocknote_appear_clock.start();
        }
    break;
    case 3:
        if(auto elapsed_time = blocknote_appear_clock.getElapsedTime(); elapsed_time < blocknote_appear_time)
        {
            static auto ease_out_cubic = [](float x /*0...1*/) -> float /*0...1*/ {
                return 1 - std::pow(1 - x, 3);
            };
            auto [pos, size] = blocknote.get_global_bounds();
            auto wy = get_wsize<float>().y;
            blocknote.setPosition({
                ease_out_cubic(elapsed_time / blocknote_appear_time) * size.x - size.x,
                wy
            });
        }
        else state++;
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