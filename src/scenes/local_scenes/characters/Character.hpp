#pragma once

#include "../../SceneManager.hpp"
#include "../../../res/res.hpp"
#include "../../../ui/widget/widget.hpp"

class Character : public SceneManager::Scene
{
public:
    Character(res::Texture &texture, ui::OriginState origin_state);
    void resize() override;
    void update(unused double delta_time) override = 0;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    sf::Sprite sprite;
    ui::OriginState origin_state;
};