#include "MainMenu.hpp"

MainMenu::MainMenu()
{
    shape.setFillColor(sf::Color(100, 250, 50));
    auto ws = get_window().getSize();
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
        (ws.y / 3.f) * 2 + start.get_global_bounds().size.y
    });

    start.on_release = [&](){
        // SceneManager::add_scene<MainMenu>();
        // dbg << __func__;
    };
    exit.on_release = [&](){
        std::exit(0);
        // quit();
    };
}

void MainMenu::update([[maybe_unused]] double delta_time)
{
    start.update(delta_time);
    exit.update(delta_time);
    //     quit();
}

void MainMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    auto drw = [&](auto s){
        target.draw(s, states);
    };
    drw(logo);
    drw(start);
    drw(exit);
    drw(shape);
}
