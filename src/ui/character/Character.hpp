#pragma once

#include "../widget.hpp"
#include "../sprite/Sprite.hpp"
#include "../label/StampLabel.hpp"
#include "../../res/res.hpp"
#include "../../core/pauseble_clock/PausebleClock.hpp"
#include "../../core/Animation.hpp"
#include "../../core/logger/Logger.hpp"

namespace ui
{

class Character : public BaseWidget<>
{
public:
    Character(res::Texture &texture,
              ui::OriginState origin_state = ui::OriginState::left_down,
              std::vector<sf::String> phrases = {L"default phrase"},
              sf::Time pause_after_talk = sf::seconds(0.7),
              sf::Time appear_time = sf::seconds(0.7));
    void restart_with_phrases(std::vector<sf::String>&& new_phrases);
    void resize();
    void update(double delta_time) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    no_discard sf::FloatRect get_global_bounds() const override;  
    no_discard bool is_end_of_speech() const;
    PausebleClock animation_clock;

private:
    bool is_end;
    bool is_appear;
    OriginState origin_state;
    std::size_t phrases_iter;
    std::vector<sf::String> phrases;
    sf::Time pause_after_talk;
    StampLabelMusic label;
    Sprite sprite;
    sf::Time appear_time;
    std::pair<float, float> anim_poses;
};

} // ui