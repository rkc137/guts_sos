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
    answer_paper.resize();

    blocknote_tutorial.setPosition({0, wsize.y});
    blocknote_morse.setPosition({0, wsize.y});
    blocknote_mission.setPosition({wsize.x, 0});
    answer_paper.setPosition({wsize.x, 0});
}

void Level1::update(unused double delta_time)
{
    auto wsize = get_wsize<float>();
    auto elapsed_time = animation_clock.get_elapsed_time();
    // i need c++26 std::bind_back<Fn> sooo bad
    auto blocknote_animation = [&](std::pair<float, float> range){
        return anim::interpolate<anim::ease_out_cubic>(range, elapsed_time, blocknote_appear_time);
    };

    background.update(delta_time);
    switch(state)
    {
    case 0:
        shaker.update(delta_time);
        if(!shaker.is_done())
            break;
        draws = { troop };
        troop.restart_with_phrases(LC::choose_vector({
            {LC::Lang::eng, {L"Sir, it's time for us to retreat", L"They will soon surround us"}},
            {LC::Lang::rus, {L"Сэр, нам пора отсупать", L"Они скоро окружат нас"}}
        }));
        state++;
    [[fallthrough]];
    case 1:
        troop.update(delta_time);
        if(!troop.is_end_of_speech())
            break;
        draws = { commander };
        commander.restart_with_phrases(LC::choose_vector({
            {LC::Lang::eng, {L"No, we're not backing down", L"artiller support is still with us", L"Commo, check the telegraph!"}}
        }));
        state++;
    [[fallthrough]];
    case 2:
        commander.update(delta_time);
        if(!commander.is_end_of_speech())
            break;
        draws = { troop };
        troop.restart_with_phrases(LC::choose_vector({
            {LC::Lang::eng, {
                L"Commo, send them \"QRV?\"",
                L"that means \"Are you ready?\"",
                L"we will know they ready, if answer will be same code without \"?\""
            }}
        }));
        state++;
    break;
    case 3:
        troop.update(delta_time);
        if(troop.is_end_of_speech())
        {
            state++;
            draws = { blocknote_tutorial, blocknote_morse, blocknote_mission, telegraph };

            auto [post, sizet] = blocknote_tutorial.get_global_bounds();
            auto [posm, sizem] = blocknote_morse.get_global_bounds();
            auto [posmi, sizemi] = blocknote_mission.get_global_bounds();
            blocknote_tutorial.setPosition({-sizet.x, wsize.y});
            blocknote_morse.setPosition({-sizem.x, wsize.y});
            blocknote_mission.setPosition({wsize.x, -sizemi.y});
            answer_paper.setPosition({-wsize.x, sizemi.y * .5f});

            animation_clock.restart();
        }
    break;
    case 4:
    {
        if(elapsed_time > tutorial_time + blocknote_appear_time + blocknote_appear_time)
        {
            telegraph.set_mission(are_you_ready);
            draws = { blocknote_morse, blocknote_mission, answer_paper, telegraph };
            state++;
        }
        else if(elapsed_time < blocknote_appear_time)
        {
            blocknote_tutorial.setPosition({
                blocknote_animation({-blocknote_tutorial.get_global_bounds().size.x, 0}),
                wsize.y
            });
        }
        else if(elapsed_time > blocknote_appear_time + tutorial_time)
        {
            elapsed_time -= blocknote_appear_time + tutorial_time;
            blocknote_morse.setPosition({
                blocknote_animation({-blocknote_morse.get_global_bounds().size.x, 0}),
                wsize.y
            });
            blocknote_tutorial.setPosition({
                blocknote_animation({0, -blocknote_tutorial.get_global_bounds().size.x}),
                wsize.y
            });
            blocknote_mission.setPosition({
                wsize.x,
                blocknote_animation({-blocknote_mission.get_global_bounds().size.y, 0})
            });
        }
    }
    break;
    case 5:
        telegraph.update(delta_time);
        if(telegraph.mission_done_pause())
        {
            state++;
            print.play();
            animation_clock.restart();
        }
    break;
    case 6:
        if(animation_clock.get_elapsed_time() <= blocknote_appear_time)
        {
            answer_paper.setPosition({
                blocknote_animation({answer_paper.get_global_bounds().size.x + wsize.x, wsize.x}),
                blocknote_mission.get_global_bounds().size.y / 2
            });
        }
        else if(animation_clock.get_elapsed_time() <= blocknote_appear_time + blocknote_appear_time + blocknote_appear_time)
        {
            elapsed_time -= blocknote_appear_time + blocknote_appear_time;
            answer_paper.setPosition({
                blocknote_animation({wsize.x, answer_paper.get_global_bounds().size.x + wsize.x}),
                blocknote_mission.get_global_bounds().size.y / 2
            });
            blocknote_morse.setPosition({
                blocknote_animation({0, -blocknote_morse.get_global_bounds().size.x}),
                wsize.y
            });
            blocknote_mission.setPosition({
                wsize.x,
                blocknote_animation({0, -blocknote_mission.get_global_bounds().size.y})
            });
        }
        else
        {
            state++;
            draws = { commander };
            commander.restart_with_phrases(LC::choose_vector({
                {LC::Lang::eng, {
                    L"now send coordinates of these bastards",
                    L"our guys gonna give em some shake!"
                }}
            }));
            auto mission = "E67F50";
            telegraph.set_mission(mission);
            blocknote_mission.label.set_string(mission);
        }

    break;
    case 7:
        commander.update(delta_time);
        if(commander.is_end_of_speech())
        {
            state++;
            draws = { blocknote_mission, telegraph, blocknote_morse };

            auto [posm, sizem] = blocknote_morse.get_global_bounds();
            auto [posmi, sizemi] = blocknote_mission.get_global_bounds();
            blocknote_morse.setPosition({-sizem.x, wsize.y});
            blocknote_mission.setPosition({wsize.x, -sizemi.y});

            animation_clock.restart();
        }
    break;
    case 8:
        telegraph.update(delta_time);
        if(telegraph.mission_done_pause())
        {
            state++;
        }
        if(elapsed_time <= blocknote_appear_time)
        {
            blocknote_morse.setPosition({
                blocknote_animation({-blocknote_morse.get_global_bounds().size.x, 0}),
                wsize.y
            });
            blocknote_mission.setPosition({
                wsize.x,
                blocknote_animation({-blocknote_mission.get_global_bounds().size.y, 0})
            });
        }
    break;
    case 9:
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
