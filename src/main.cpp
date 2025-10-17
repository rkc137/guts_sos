#include <SFML/System.hpp>

// #include <queue>
#include <memory>

#include "res/res.hpp"
#include "core/Window.hpp"
#include "scenes/Opening.hpp"

int main()
{
    res::load();
    Window window;
    SceneManager::add_scene<Level1>();

    ui::Label fps_label;
    fps_label.set_fill_color(sf::Color::White);
    fps_label.set_origin_state(ui::OriginState::left_up);

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
                size += {
                    (size.x == 0) * 60u,
                    (size.y == 0) * 60u
                };
                window.setSize(size);
                window.setView({
                    static_cast<sf::Vector2f>(size) / 2.f,
                    static_cast<sf::Vector2f>(size)
                });
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
        window.draw(fps_label);
        window.display();
        window.clear();

        fps_label.set_string(std::to_string(1 / delta_time));
    }
    
    return 0;
}