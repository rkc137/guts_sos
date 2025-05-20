#pragma once

#include "../SceneManager.hpp"
#include "../../res/res.hpp"
#include "../local_scenes/BasementBackground.hpp"

class Level1 : public SceneManager::Scene
{
public:
    void resize() override;
    void update(double delta_time) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    BasementBackground background;
};