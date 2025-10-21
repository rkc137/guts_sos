#pragma once

#include "../../res/res.hpp"
#include "../../ui/sprite/Sprite.hpp"
#include "../../ui/label/label.hpp"
#include "../../core/pauseble_clock/PausebleClock.hpp"
#include "../SceneManager.hpp"
#include "../local_scenes/Telegraph.hpp"
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
    std::vector<std::reference_wrapper<sf::Drawable>> draws;
    sf::Sound incoming{res::incoming};
    Shaker shaker{sf::seconds(2.4), 80};
    Character troop{res::troop, ui::OriginState::right_down, { "f"}};
        // L"Sir, it's time for us to retreat", L"They will soon surround us"}};
    Character commander{res::commander, ui::OriginState::left_down, { "fr"}};
        // L"No, we're not backing down", L"artiller support is still with us", L"Commo, check the telegraph!"}};
    Sprite blocknote_morse{res::blocknote_morse, ui::OriginState::left_down};
    class BlocknoteTutorial : public virtual ui::BaseWidget<>
    {
    public:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        sf::FloatRect get_global_bounds() const override;
        void resize();
        ui::Label label{
            L"Press space key to use\n"
            L"telegraph. Short press\n"
            L"makes dots and long\n"
            L"makes dash. If you make\n"
            L"mistake, make 8 dots to\n"
            L"erase last letter.",
            res::too_much_ink,
            sf::Color::White,
            40,
            ui::OriginState::left_up
        };
        Sprite sprite{res::blocknote_blank, ui::OriginState::left_down};
    } blocknote_tutorial;
    PausebleClock blocknote_appear_clock;
    const sf::Time blocknote_appear_time = sf::seconds(1.5);
    const sf::Time tutorial_time = sf::seconds(15);
    BasementBackground background;
    Telegraph telegraph;
};