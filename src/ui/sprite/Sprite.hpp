#pragma once

#include <SFML/Graphics.hpp>

#include "../widget/widget.hpp"
#include "../../res/res.hpp"

class Sprite : public virtual ui::BaseWidget<>
{
public:
    Sprite(sf::Texture &texture, ui::OriginState origin_state = ui::OriginState::left_up);
    void resize();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect get_global_bounds() const override;
    sf::Sprite sprite;
};