#pragma once

#include "SceneManager.hpp"

class Curtain : public SceneManager::Scene
{
public:
    Curtain(sf::Time duration = sf::seconds(3), bool is_quiting_on_time = true);
    void update(double delta_time) override;
    void resize() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool should_quit = false;
private:
    bool is_quiting_on_time = true;
    sf::RectangleShape shape;
    sf::Clock clock;
    sf::Time duration = sf::seconds(3);
};