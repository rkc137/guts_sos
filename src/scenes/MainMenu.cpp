#include "MainMenu.hpp"

MainMenu::MainMenu(sf::RenderWindow &window) 
    : window(window),
      logo(window, res::app_name, sf::Color::Black, 80, res::cybersomething) //(res::cybersomething, res::app_name, 80, sf::Color::Black})
{
    dbg << __func__;
    shape.setFillColor(sf::Color(100, 250, 50));
}

MainMenu::~MainMenu()
{
    dbg << __func__;
}

void MainMenu::update(double delta_time)
{
    shape.setRadius(100 + delta_time * 0);
    shape.setPosition({
        double(int(shape.getPosition().x + 1) % 100),
        0
    });
    // if(shape.getPosition().x > 100)
    //     quit();
}

void MainMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    auto drw = [&](auto s){
        target.draw(s, states);
    };
    
    drw(shape);
}
