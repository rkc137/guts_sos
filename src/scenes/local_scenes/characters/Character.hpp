#pragma once

#include "../../SceneManager.hpp"
#include "../../../res/res.hpp"
#include "../../../ui/label/StampLabel.hpp"

class Character : public SceneManager::Scene
{
public:
    Character(res::Texture &texture,
              ui::OriginState origin_state = ui::OriginState::left_down,
              std::vector<sf::String> phrases = {L"default phrase"},
              sf::Time pause_after_talk = sf::seconds(2));
    void set_pheases(std::vector<sf::String>&& new_phrases);
    void resize() override;
    void update(double delta_time) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    no_discard bool is_end_of_speech() const;
private:
    bool is_end = false;
    sf::Sprite sprite;
    ui::OriginState origin_state;
    std::vector<sf::String> phrases;
    std::size_t phrases_iter = 0;
    ui::StampLabelMusic label;
    sf::Time pause_after_talk;
};