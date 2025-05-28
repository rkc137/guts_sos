#pragma once

#include "../SceneManager.hpp"

class Shaker : public SceneManager::Scene
{
public:
    Shaker(sf::Time shake_time, float in_power) : shake_time(shake_time), in_power(in_power)
    {}
    void resize() override;
    void update(unused double delta_time) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::Time shake_time = sf::seconds(2.4);
    const float in_power = 100;
    float power = in_power;
    sf::Clock shale_clock;
    sf::View original_view;
};
