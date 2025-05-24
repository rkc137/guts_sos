#pragma once

#include "../../SceneManager.hpp"
#include "../../../res/res.hpp"
#include "../../../ui/label/StampLabel.hpp"

class Character : public SceneManager::Scene
{
public:
    Character(res::Texture &texture, ui::OriginState origin_state, sf::String phrase);
    void resize() override;
    void update(unused double delta_time) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    sf::Sprite sprite;
    ui::OriginState origin_state;
    ui::StampLabelMusic phrase;
};