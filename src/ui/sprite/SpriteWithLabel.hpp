#pragma once

#include "Sprite.hpp"
#include "../label/label.hpp"

namespace ui
{

class SpriteWithLabel : public virtual ui::BaseWidget<>
{
public:
    SpriteWithLabel(sf::String text, ui::OriginState text_state, Sprite &&sprite);
    SpriteWithLabel() = delete;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect get_global_bounds() const override;
    void resize();

    // TODO: make text fit in bounds
    ui::Label label;
    Sprite sprite;
};

}