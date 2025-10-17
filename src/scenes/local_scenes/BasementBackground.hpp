#pragma once

#include <numbers>

#include "../SceneManager.hpp"
#include "../../res/res.hpp"

class BasementBackground : public SceneManager::Scene
{
public:
    BasementBackground();
    void resize() override;
    void update(double delta_time) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::Angle offset_angle;
    sf::Time offset_time;
private:
    sf::Angle swaying_time_angle = sf::degrees(1.5);
    sf::Time swaying_time = sf::seconds(10);
    sf::Sprite background{res::bunker};
    sf::Sprite light{res::light};
    sf::Clock clock;
};