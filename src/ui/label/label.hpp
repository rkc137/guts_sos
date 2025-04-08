#pragma once

#include <SFML/Graphics.hpp>

#include "../../res/res.hpp"
#include "../widget/widget.hpp"

namespace ui
{

class Label : public BaseWidget<>
{
public:
    enum class OriginState
    {
        center,
        left_up
    };

    explicit Label(const sf::String str_text = "", 
                    const sf::Font &font = res::default_font,
                    const sf::Color &color = sf::Color::Black,
                    unsigned int ch_size = 30,
                    OriginState state = OriginState::center);
    
    explicit Label(sf::Text&& text,
                    const sf::Color &color = sf::Color::Black,
                    OriginState state = OriginState::center);
    
    void set_string(sf::String &&str);
    sf::String get_string();
    void set_origin_state(OriginState state);
    OriginState get_origin_state();
    void set_char_size(unsigned int ch_size);
    unsigned int get_char_size();
    void set_fill_color(sf::Color color);
    sf::Color get_fill_color();
    void update_origin();
    
    sf::FloatRect get_global_bounds() const override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    OriginState origin_state;
    sf::Text text;
};

}