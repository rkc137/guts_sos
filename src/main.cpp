#include <memory>

#include "res/res.hpp"
#include "core/Window.hpp"
#include "scenes/Lang.hpp"

int main()
{
    try
    {
        res::load();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 100;
    }

    Window window;
    SceneManager::start_scene<ChooseLang>();


    sf::Clock clock;
    double delta_time = 0.01;
    for(; window.isOpen(); delta_time = clock.restart().asSeconds())
    {
        auto scene = SceneManager::get_current();

        while(const std::optional event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>()) window.close();
            else if(const auto* resized = event->getIf<sf::Event::Resized>())
            {
                auto size = resized->size;
                static const sf::Vector2u minimal_size = {400, 300};
                size = {
                    size.x < minimal_size.x ? minimal_size.x : size.x,
                    size.y < minimal_size.y ? minimal_size.y : size.y
                };
                window.setSize(size);
                window.setView({
                    static_cast<sf::Vector2f>(size) / 2.f,
                    static_cast<sf::Vector2f>(size)
                });
                scene->resize();
            }
            else if(const auto* k = event->getIf<sf::Event::KeyPressed>())
            {
                using namespace sf::Keyboard;
                switch(k->code)
                {
                case Key::F11:
                    window.change_fullscreen();
                    scene->resize();
                break;
                default:
                }
            }
        }

        scene->update(delta_time);
        window.draw(*scene);

#ifndef NDEBUG
        static auto fps_label = std::invoke([&]{
            ui::Label fps;
            fps.set_fill_color(sf::Color::White);
            fps.set_origin_state(ui::OriginState::left_up);
            return fps;
        });
        fps_label.set_string(std::to_string(static_cast<int>(1 / delta_time)));
        window.draw(fps_label);
#endif
        window.display();
        window.clear();
    }

    return 0;
}