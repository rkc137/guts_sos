#include <SFML/System.hpp>

#include <queue>
#include <memory>

#include "res/res.hpp"

#include "Scenes/MainMenu.hpp"
#include "ui/widget/widget.hpp"


int main()
{
    sf::RenderWindow window(
        sf::VideoMode({1280, 720}),
        res::app_name,
        sf::State::Windowed
    );
    DefaultWindowWrap::set_window_wrap_ptr(&window);

    window.setFramerateLimit(60);
    
    
    res::load();
    SceneManager::add_scene<MainMenu>();
 
    sf::Clock clock;
    double delta_time = 0;
    for(; window.isOpen(); delta_time = clock.restart().asSeconds())
    {
        while(const std::optional event = window.pollEvent())
            if(event->is<sf::Event::Closed>())
                window.close();
            // else if(event->is<sf::Event::Resized>())
            //     window.setView(sf::View{sf::Vector2u{}, window.getSize()});
        
        try {
            auto scene = SceneManager::get_current();
            scene->update(delta_time);
            window.draw(*scene);
        }
        catch(...) {
            dbg << "add new main menu scene";
            SceneManager::add_scene<MainMenu>();
        }

        window.display();
        window.clear();
        
        if(auto fps = 1 / delta_time; fps < 24)
            dbg << fps;
    }
    
    return 0;
}