#pragma once

#include "../SceneManager.hpp"
#include <functional>

class Curtain : public SceneManager::Scene
{
public:
    Curtain(bool should_waiting_response = false,
            sf::Time uppear_duration = sf::seconds(2),
            sf::Time showing_duration = sf::seconds(3),
            sf::Time disappear_duration = sf::seconds(1.5));
    void update(double delta_time) override;
    void resize() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool is_done();
    void let_go(std::function<void()> on_end);
private:
    enum States 
    {
        uppearing,
        showing,
        disappearing,
        done
    } state = uppearing;

    float alpha = 0;
    bool is_waiting = true;
    bool should_waiting_response;
    std::optional<std::function<void()>> on_exit;
    sf::Time uppear_duration;
    sf::Time showing_duration;
    sf::Time disappear_duration;
    sf::RectangleShape shape;
    sf::Clock clock;
};