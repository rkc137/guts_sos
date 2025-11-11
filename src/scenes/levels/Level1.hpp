#pragma once

#include "../../core/pauseble_clock/PausebleClock.hpp"
#include "../../core/Animation.hpp"
#include "../../core/LocalizedText.hpp"
#include "../../res/res.hpp"
#include "../../ui/sprite/Sprite.hpp"
#include "../../ui/label/label.hpp"
#include "../../ui/character/Character.hpp"
#include "../SceneManager.hpp"
#include "../local_scenes/Telegraph.hpp"
#include "../local_scenes/BasementBackground.hpp"
#include "../local_scenes/Shaker.hpp"

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
    ui::Character troop{res::troop, ui::OriginState::right_down};
    ui::Character commander{res::commander, ui::OriginState::left_down};
    sf::String mission_text = "SOS";
    Sprite blocknote_morse{res::blocknote_morse, ui::OriginState::left_down};

    class BlocknoteWithText : public virtual ui::BaseWidget<>
    {
    public:
        BlocknoteWithText(sf::String text, ui::OriginState text_state, Sprite &&sprite);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        sf::FloatRect get_global_bounds() const override;
        void resize();
    
        // TODO: make text fit in bounds
        ui::Label label;
        Sprite sprite;
    }
    blocknote_tutorial{
        L"Press space key to use\n"
        L"telegraph. Short press\n"
        L"makes dots and long\n"
        L"makes dash. Combine\n"
        L"them to make letters.\n"
        L"Wait a little bit to\n"
        L"make a space. If you\n"
        L"make a mistake, make 8\n"
        L"dots to erase last\n" L"letter.",
        ui::OriginState::left_up,
        {res::blocknote_blank, ui::OriginState::left_down}
    },
    blocknote_mission{
        L"try to send a " + mission_text,
        ui::OriginState::left_down,
        {res::blocknote_onside, ui::OriginState::right_up}
    };

    PausebleClock animation_clock;
    const sf::Time blocknote_appear_time = sf::seconds(1.5);
    const sf::Time tutorial_time = sf::seconds(1);
    BasementBackground background;
    Telegraph telegraph;
};