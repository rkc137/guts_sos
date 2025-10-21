#include "Level1.hpp"

Level1::Level1()
{
    incoming.play();
}

void Level1::resize()
{
    auto wsize = get_wsize<float>();
    background.resize();
    commander.resize();
    troop.resize();
    shaker.resize();
    telegraph.resize();
    blocknote_tutorial.resize();
    blocknote_tutorial.setPosition({0, wsize.y});
    blocknote_morse.setPosition({0, wsize.y});
    
    auto base_scale = res::get_scale(wsize);
    auto texture_size = static_cast<sf::Vector2f>(blocknote_morse.sprite.getTexture().getSize());
    auto scaled_size = sf::Vector2f(texture_size.x * base_scale.x, texture_size.y * base_scale.y);
    
    if(auto ceiling = wsize.y * 0.8f; scaled_size.y > ceiling)
    {
        auto height_scale = ceiling / texture_size.y;
        blocknote_morse.setScale({height_scale, height_scale});
    }
    else
        blocknote_morse.setScale(base_scale);
}

void Level1::update(unused double delta_time)
{
    static auto ease_out_cubic = [](float x /*0...1*/) -> float /*0...1*/ {
        return 1 - std::pow(1 - x, 3);
    };
    background.update(delta_time);
    switch(state)
    {
    case 0:
        shaker.update(delta_time);
        if(shaker.is_done())
        {
            state++;
            draws = { troop };
        }
    break;
    case 1:
        troop.update(delta_time);
        if(troop.is_end_of_speech())
        {
            state++;
            draws = { commander };
        }
    break;
    case 2:
        commander.update(delta_time);
        if(commander.is_end_of_speech())
        {
            state++;
            draws = { blocknote_tutorial, blocknote_morse };
            auto [post, sizet] = blocknote_tutorial.get_global_bounds();
            blocknote_tutorial.setPosition({-sizet.x, get_wsize<float>().y});
            auto [posm, sizem] = blocknote_tutorial.get_global_bounds();
            blocknote_morse.setPosition({-sizem.x, get_wsize<float>().y});
            blocknote_appear_clock.start();
        }
    break;
    case 3:
    {    
        telegraph.update(delta_time);
        auto elapsed_time = blocknote_appear_clock.getElapsedTime();
        if(elapsed_time > tutorial_time + blocknote_appear_time + blocknote_appear_time)
        {
            draws = { blocknote_morse, telegraph };
            state++;
        }
        else if(elapsed_time < blocknote_appear_time)
        {
            auto [pos, size] = blocknote_tutorial.get_global_bounds();
            blocknote_tutorial.setPosition({
                ease_out_cubic(elapsed_time / blocknote_appear_time) * size.x - size.x,
                get_wsize<float>().y
            });
        }
        else if(elapsed_time > blocknote_appear_time + tutorial_time)
        {
            elapsed_time -= blocknote_appear_time + tutorial_time;
            auto [pos, size] = blocknote_morse.get_global_bounds();
            blocknote_morse.setPosition({
                ease_out_cubic(elapsed_time / blocknote_appear_time) * size.x - size.x,
                get_wsize<float>().y
            });
        }
    }
    break;
    case 4:
        telegraph.update(delta_time);
    break;
    default:
    break;
    }
}

void Level1::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(background, states);
    for(auto &d : draws)
        target.draw(d, states);
}

void Level1::BlocknoteTutorial::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite, states);
    target.draw(label, states);
}

sf::FloatRect Level1::BlocknoteTutorial::get_global_bounds() const
{
    return sprite.get_global_bounds();
}

void Level1::BlocknoteTutorial::resize()
{
    auto wsize = get_wsize<float>();
    auto base_scale = res::get_scale(wsize);
    auto texture_size = static_cast<sf::Vector2f>(sprite.sprite.getTexture().getSize());
    auto scaled_size = sf::Vector2f(texture_size.x * base_scale.x, texture_size.y * base_scale.y);
    
    if(auto ceiling = wsize.y * 0.8f; scaled_size.y > ceiling)
    {
        auto height_scale = ceiling / texture_size.y;
        sprite.setScale({height_scale, height_scale});
    }
    else
        sprite.setScale(base_scale);

    auto bsize = get_global_bounds().size;
    label.set_char_size(wsize.y / 21);
    label.setPosition({bsize.x / 10, -bsize.y + bsize.y / 10});
}
