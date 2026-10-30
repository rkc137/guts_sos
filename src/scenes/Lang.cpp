#include "Lang.hpp"
#include "Opening.hpp"

ChooseLang::ChooseLang()
{
    rus.on_release = [&]{
        res::load_texts(res::Lang::rus);
        SceneManager::start_scene<Opening>();
    };
    eng.on_release = [&]{
        res::load_texts(res::Lang::eng);
        SceneManager::start_scene<Opening>();
    };
}

void ChooseLang::resize()
{
    auto ws = get_wsize<>();

    rus.set_char_size(ws.y / 10);
    eng.set_char_size(ws.y / 10);
    rus.setPosition({ws.x / 2.f - rus.get_global_bounds().size.x, ws.y / 2.5f});
    eng.setPosition({ws.x / 2.f + rus.get_global_bounds().size.x, ws.y / 2.5f});
}

void ChooseLang::update(double delta_time)
{
    rus.update(delta_time);
    eng.update(delta_time);
}

void ChooseLang::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(rus, states);
    target.draw(eng, states);
}
