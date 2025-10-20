#pragma once

#include <chrono>

#include "../../res/res.hpp"
#include "../../ui/sprite/Sprite.hpp"
#include "../../core/pauseble_clock/PausebleClock.hpp"
#include "../SceneManager.hpp"
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
    Character troop{res::troop, ui::OriginState::right_down, {
        L"Sir, it's time for us to retreat", L"They will soon surround us"}};
    Character commander{res::commander, ui::OriginState::left_down, {
        L"No, we're not backing down", L"artiller support is still with us", L"Commo, check the telegraph!"}};
    Sprite blocknote{res::blocknote_morse, ui::OriginState::left_down};
    PausebleClock blocknote_appear_clock;
    sf::Time blocknote_appear_time = sf::seconds(1.5);
    BasementBackground background;
};