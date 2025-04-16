#include "MainMenu.hpp"

MainMenu::MainMenu()
{
    start.on_release = [&](){
        // if(res::is_no_save)
        // {
        //     SceneManager::add_scene<Intro>();
        //     SceneManager::add_scene<lvl1>();
        // }
        // dbg << __func__;
    };
    exit.on_release = [&](){
        std::exit(0);
        // quit();
    };
}

void MainMenu::update(unused double delta_time)
{
    start.update(delta_time);
    exit.update(delta_time);
    telegraph.update(delta_time);
    //     quit();
}

void MainMenu::resize()
{
    auto ws = get_window().getSize();
    
    logo.set_char_size(ws.y / 7);
    exit.set_char_size(ws.y / 15);
    start.set_char_size(ws.y / 15);
    author.set_char_size(ws.y / 17); 

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
    author.setPosition({0, static_cast<float>(ws.y)});
    
    telegraph.resize();
}

void MainMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    auto drw = [&](this auto&& self, auto s, auto... d){
        target.draw(s, states);
        if constexpr (sizeof...(d) > 0)
            self(d...);
    };
    drw(logo, start, exit, author, telegraph);
}
