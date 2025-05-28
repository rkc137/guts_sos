#pragma once

#include "../../SceneManager.hpp"
#include "../../../res/res.hpp"
#include "../../../ui/label/StampLabel.hpp"

class Character : public SceneManager::Scene
{
public:
    Character(res::Texture &texture, ui::OriginState origin_state, sf::String phrase = "default phrase", sf::Time pause_after_talk = sf::seconds(2));
    void set_phease(sf::String new_phrase);
    void resize() override;
    void update(unused double delta_time) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::Time last_time_spoked_letter() const;
    bool is_spoked() const;
    bool is_end_of_phrase() const;
private:
    sf::Sprite sprite;
    ui::OriginState origin_state;
    ui::StampLabelMusic phrase;
    sf::Time pause_after_talk;
};