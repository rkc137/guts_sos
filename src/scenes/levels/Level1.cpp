#include "Level1.hpp"

Level1::Level1()
{
    incoming.play();
    res::distance_battle.setLooping(true);
    res::distance_battle.play();
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
    blocknote_morse.resize();
    blocknote_mission.resize();
    
    blocknote_tutorial.setPosition({0, wsize.y});
    blocknote_morse.setPosition({0, wsize.y});
    blocknote_mission.setPosition({wsize.x, 0});
}

void Level1::update(unused double delta_time)
{
    static auto ease_out_cubic = [](float x /*0...1*/) -> float /*0...1*/ {
        return 1 - std::pow(1 - x, 3);
    };
    auto wsize = get_wsize<float>();
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
            draws = { blocknote_tutorial, blocknote_morse, blocknote_mission, telegraph };
            
            auto [post, sizet] = blocknote_tutorial.get_global_bounds();
            auto [posm, sizem] = blocknote_morse.get_global_bounds();
            auto [posmi, sizemi] = blocknote_mission.get_global_bounds();
            blocknote_tutorial.setPosition({-sizet.x, wsize.y});
            blocknote_morse.setPosition({-sizem.x, wsize.y});
            blocknote_mission.setPosition({wsize.x, -sizemi.y});
            
            blocknote_appear_clock.start();
        }
    break;
    case 3:
    {    
        telegraph.update(delta_time);
        auto elapsed_time = blocknote_appear_clock.getElapsedTime();
        if(elapsed_time > tutorial_time + blocknote_appear_time + blocknote_appear_time)
        {
            draws = { blocknote_morse, blocknote_mission, telegraph };
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
            {
                auto [pos, size] = blocknote_morse.get_global_bounds();
                blocknote_morse.setPosition({
                    ease_out_cubic(elapsed_time / blocknote_appear_time) * size.x - size.x,
                    get_wsize<float>().y
                });
            }
            {
                auto [pos, size] = blocknote_tutorial.get_global_bounds();
                blocknote_tutorial.setPosition({
                    -ease_out_cubic(elapsed_time / blocknote_appear_time) * size.x,
                    get_wsize<float>().y
                });
            }
            {
                auto [pos, size] = blocknote_mission.get_global_bounds();
                // wsize.x, -size.y
                blocknote_mission.setPosition({
                    wsize.x,
                    ease_out_cubic(elapsed_time / blocknote_appear_time) * size.y - size.y
                });
            }
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

void Level1::BlocknoteWithText::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite, states);
    target.draw(label, states);
}

sf::FloatRect Level1::BlocknoteWithText::get_global_bounds() const
{
    return sprite.get_global_bounds();
}

void Level1::BlocknoteWithText::resize()
{
    sprite.resize();
    auto wsize = get_wsize<float>();
    auto bsize = get_global_bounds().size;
    label.set_char_size(wsize.y / 21);
    switch(label.get_origin_state())
    {
    case ui::OriginState::left_down:
        label.setPosition({bsize.x / 10, -bsize.y + bsize.y / 10});
    break;
    case ui::OriginState::left_up:
        label.setPosition({bsize.x / 10, -bsize.y + bsize.y / 10});
    break;
    default:
        throw std::runtime_error("not supported state");
    }
}

Level1::BlocknoteWithText::BlocknoteWithText(sf::String text, ui::OriginState text_state, Sprite &&sprite) :
    label{
        text,
        res::too_much_ink,
        sf::Color::White
    },
    sprite{sprite}
{
    label.set_origin_state(text_state);
}
