#pragma once

#include <SFML/Graphics.hpp>

#include "../../res/res.hpp"
#include "../widget/widget.hpp"

namespace ui
{

class Label : public BaseWidget<>
{
public:
    explicit Label(const std::string str_text = "", 
                    const sf::Font &font = res::default_font,
                    const sf::Color &color = sf::Color::Black,
                    unsigned int ch_size = 30);
               
    explicit Label(sf::Text&& text, const sf::Color &color = sf::Color::Black);

    void set_char_size(unsigned int ch_size);
    unsigned int get_char_size();
    void set_fill_color(sf::Color color);
    sf::Color get_fill_color();
    void update_origin();
    
    sf::FloatRect get_global_bounds() const override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Text text;
};

}