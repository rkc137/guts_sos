#include <SFML/System.hpp>

#include <queue>
#include <memory>

#include "res/res.hpp"
#include "core/Window.hpp"
#include "Scenes/MainMenu.hpp"
#include "Scenes/Opening.hpp"

int main()
{
    res::load();
    Window window;
    SceneManager::add_scene<Opening>();
    sf::Clock clock;
    double delta_time = 0;
    for(; window.isOpen(); delta_time = clock.restart().asSeconds())
    {
        auto scene = SceneManager::get_current();
            
        while(const std::optional event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>()) window.close();
            else if(const auto* resized = event->getIf<sf::Event::Resized>())
            {
                auto size = resized->size; 
                window.setView(sf::View{{size.x / 2.f, size.y / 2.f}, sf::Vector2f{size}});
                scene->resize();
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::F11))
        {
            window.change_fullscreen();
            scene->resize();
        }

        scene->update(delta_time);
        window.draw(*scene);
        window.display();
        window.clear();
        
        // if(auto fps = 1 / delta_time; fps < 24)
        //     dbg << fps;
    }
    
    return 0;
}