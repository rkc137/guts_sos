#include "main_menu.hpp"

namespace ui
{

Main_menu::Main_menu(sf::RenderWindow &window)
            : window(window),
              logo(window, "cowhouse"),
              start(Label(window, "start")),
              exit(Label(window, "exit")),
              settings(Label(window, "settings"))
{
    sf::View view({}, static_cast<sf::Vector2f>(window.getSize()));
    window.setView(view);


    start.on_release = [&]() -> void
    {
        std::cout << "start game\n";
    };
    settings.on_release = [&]() -> void
    {
        std::cout << "settings\n";
    };
    exit.on_release = [&]() -> void 
    {
        std::exit(0);
    };
}

void Main_menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(logo, states);
    target.draw(start, states);
    target.draw(settings, states);
    target.draw(exit, states);
}

void Main_menu::update(double delta_time)
{
    int height = window.getSize().y;
    int width = window.getSize().x;

        
    logo.text.setCharacterSize(height / 5);
    logo.update_origin();
    for(auto b : {&start, &settings, &exit})
        b->text.setCharacterSize(height / 18);
    
    logo.setPosition(0, height / 3 - height / 2);
    start.setPosition(0, (height / 3) * 2 - height / 2);
    settings.setPosition(0, start.text.getCharacterSize() * 2 + start.getPosition().y);
    exit.setPosition(0, settings.text.getCharacterSize() * 2 + settings.getPosition().y);

    logo.update(delta_time);
    start.update(delta_time);
    settings.update(delta_time);
    exit.update(delta_time);
}

}