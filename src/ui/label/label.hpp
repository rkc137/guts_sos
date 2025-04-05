#pragma once

#include <SFML/Graphics.hpp>

#include "../../res/res.hpp"
#include "../widget/widget.hpp"

namespace ui
{

class Label : public Widget
{
public:
    explicit Label(const sf::RenderWindow &window,
                   const std::string str_text = "", 
                   const sf::Color &color = sf::Color::Black,
                   int ch_size = 30,
                   const sf::Font &font = res::default_font);
    void update_origin();
    sf::Text text;

    sf::FloatRect get_global_bounds() const override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

}