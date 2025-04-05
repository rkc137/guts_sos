#include "MainMenu.hpp"

MainMenu::MainMenu(sf::RenderWindow &window) 
    : window(window)    
    //   logo(window, res::app_name, sf::Color::Black, 80, res::cybersomething) //(res::cybersomething, res::app_name, 80, sf::Color::Black})
{
    shape.setFillColor(sf::Color(100, 250, 50));
    logo.setPosition({100, 100});
}

MainMenu::~MainMenu() {}

void MainMenu::update(double delta_time)
{
    //     quit();
}

void MainMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    auto drw = [&](auto s){
        target.draw(s, states);
    };
    drw(logo);
    drw(shape);
}
