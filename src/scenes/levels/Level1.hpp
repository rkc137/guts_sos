#pragma once

#include "../SceneManager.hpp"
#include "../../res/res.hpp"
#include "../local_scenes/BasementBackground.hpp"
#include "../local_scenes/Shaker.hpp"
#include "../local_scenes/characters/Character.hpp"

class Level1 : public SceneManager::Scene
{
public:
    Level1();
    void resize() override;
    void update(double delta_time) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    int state = 0;
    std::vector<sf::Drawable*> draws;
    sf::Sound incoming{res::incoming};
    Shaker shaker{sf::seconds(2.4), 80};
    Character commander{res::commander, ui::OriginState::left_down};
    Character troop{res::troop, ui::OriginState::right_down};
    BasementBackground background;
};