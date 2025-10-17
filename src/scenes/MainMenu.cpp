#include "MainMenu.hpp"

MainMenu::MainMenu()
{
    start.on_release = [&](){
        curtain.let_go([this](){
            // if(res::is_no_save)
            SceneManager::add_scene<Intro>();
            quit();
        });
    };
    exit.on_release = [&](){
        curtain.let_go([](){
            std::exit(0);
        });
    };
}

void MainMenu::resize()
{
    auto ws = get_wsize<>();
    
    logo.set_char_size(ws.y / 7);
    exit.set_char_size(ws.y / 15);
    start.set_char_size(ws.y / 15);

    logo.setPosition({
        ws.x / 2.f,
        ws.y / 3.f
    });
    start.setPosition({
        ws.x / 2.f,
        (ws.y / 3.f) * 2
    });
    exit.setPosition({
        ws.x / 2.f,
        (ws.y / 3.f) * 2 + start.get_global_bounds().size.y * 2
    });
    curtain.resize();
    telegraph.resize();
}

void MainMenu::update(unused double delta_time)
{
    start.update(delta_time);
    exit.update(delta_time);
    telegraph.update(delta_time);
    curtain.update(delta_time);
    //     quit();
}

void MainMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    auto drw = [&](this auto&& self, auto s, auto... d){
        target.draw(s, states);
        if constexpr (sizeof...(d) > 0)
            self(d...);
    };
    drw(logo, start, exit, telegraph, curtain);
}
