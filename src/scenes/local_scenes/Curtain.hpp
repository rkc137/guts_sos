#pragma once

#include "../SceneManager.hpp"

class Curtain : public SceneManager::Scene
{
public:
    Curtain(bool is_quiting_on_time = true,
            sf::Time uppear_duration = sf::seconds(2),
            sf::Time showing_duration = sf::seconds(3),
            sf::Time disappear_duration = sf::seconds(1.5));
    void update(double delta_time) override;
    void resize() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool is_done();
private:
    enum States 
    {
        uppearing,
        showing,
        disappearing,
        done
    } state = uppearing;

    float alpha = 0;
    bool is_quiting_on_time;
    sf::Time uppear_duration;
    sf::Time showing_duration;
    sf::Time disappear_duration;
    sf::RectangleShape shape;
    sf::Clock clock;
};