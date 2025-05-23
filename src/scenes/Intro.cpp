#include "Intro.hpp"

Intro::Intro()
{
    texts.reserve(res::intro_texts.size());
    res::carterattack.play();
    for(auto str : res::intro_texts)
        texts.emplace_back(ui::StampLabelSound{
            ui::Label{L"", res::too_much_ink, sf::Color::White},
            str,
            sf::Sound(res::stamp)
        });
}

void Intro::resize()
{
    auto ws = get_wsize<float>();
    for(auto &t : texts)
        t.set_char_size(ws.y / 20); 
                
    // char_size != y_size;
    auto y_size = [&t = texts[0]]{
        float size;
        bool set_back = t.empty();
        if(set_back)
            t.set_string("TEXT ME");
        size = t.get_global_bounds().size.y;
        if(set_back)
            t.clear();
        return size;
    }();

    sf::Vector2f offset{0, y_size * 3.5f}, first_pos = {ws.x / 2, ws.y / 3 * 1.2f};
    first_pos -= offset;
    for(auto &t : texts)
        t.setPosition(first_pos += offset);
    curtain.resize();
}

void Intro::update(unused double delta_time)
{
    if(active_text_iter < texts.size())
    {
        auto &t = texts[active_text_iter];
        t.update(delta_time);
        if(t.is_done() && text_done_check == false)
        {
            clock.restart();
            text_done_check = true;
        }
        else if(t.is_done() && clock.getElapsedTime() >= pause)
        {
            active_text_iter++;
            text_done_check = false;
        }
    }
    else if(done_check == false)
    {
        curtain.start_clock();
        clock.restart();
        done_check = true;
    }
    else
    {
        curtain.update(delta_time);
        volume = 100 - static_cast<int>(std::clamp(clock.getElapsedTime() / disappear_duration * 100, 0.f, 100.f));
        res::carterattack.setVolume(volume);
        if(curtain.is_done())
        {
            res::carterattack.stop();
            SceneManager::add_scene<Level1>();
            quit();
        }
    }
}

void Intro::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for(auto &t : texts)
        target.draw(t, states);
    target.draw(curtain, states);
}
