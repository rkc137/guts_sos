#pragma once

#include "../SceneManager.hpp"

class Shaker : public SceneManager::Scene
{
public:
    Shaker(sf::Time shake_time = sf::seconds(3), float in_power = 100);
    void resize() override;
    void update(unused double delta_time) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    no_discard bool is_done();
private:
    sf::Time shake_time;
    const float in_power;
    float power;
    sf::Clock clock;
    sf::View original_view;
};
