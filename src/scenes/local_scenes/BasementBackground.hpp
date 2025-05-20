#pragma once

#include "../SceneManager.hpp"
#include "../../res/res.hpp"

class BasementBackground : public SceneManager::Scene
{
public:
    BasementBackground();
    void resize() override;
    void update(double delta_time) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    sf::Sprite background{res::bunker};
};