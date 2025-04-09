#include <SFML/System.hpp>

#include <queue>
#include <memory>

#include "res/res.hpp"

#include "Scenes/MainMenu.hpp"
#include "ui/widget/widget.hpp"


int main()
{
    res::load();
    sf::RenderWindow window(
        sf::VideoMode({1280, 720}),
        res::app_name,
        sf::State::Windowed
    );
    window.setFramerateLimit(60);
    window.setTitle(res::app_name);
    window.setIcon(res::default_texture.copyToImage());
    DefaultWindowWrap::set_window_wrap_ptr(&window);
    // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::F11))
    // {
    //     auto *wp = &window;
    //     window.create(
    //         sf::VideoMode::getFullscreenModes().front(),
    //             res::app_name,
    //             sf::State::Fullscreen);
    //     assert(wp == &window);
    // }
    SceneManager::add_scene<MainMenu>();
    sf::Clock clock;
    double delta_time = 0;
    for(; window.isOpen(); delta_time = clock.restart().asSeconds())
    {
        auto scene = SceneManager::get_current();
            
        while(const std::optional event = window.pollEvent())
            if(event->is<sf::Event::Closed>())
            window.close();
            else if(const auto* resized = event->getIf<sf::Event::Resized>())
            {
                auto size = resized->size; 
                window.setView(sf::View{{size.x / 2.f, size.y / 2.f}, sf::Vector2f{size}});
                scene->resize();
            }

            
        scene->update(delta_time);
        window.draw(*scene);
        window.display();
        window.clear();
        
        if(auto fps = 1 / delta_time; fps < 24)
            dbg << fps;
    }
    
    return 0;
}