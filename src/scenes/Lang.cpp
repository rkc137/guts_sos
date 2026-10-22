#include "Lang.hpp"
#include "Opening.hpp"

ChooseLang::ChooseLang()
{
    auto start = [&]{
        res::load_texts();
        SceneManager::start_scene<Opening>();
    };
    rus.on_release = [&]{
        res::current_language = res::Lang::rus;
        start();
    };
    eng.on_release = [&]{
        res::current_language = res::Lang::eng;
        start();
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
