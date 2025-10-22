#pragma once

#include <SFML/Graphics.hpp>

#include "../../res/res.hpp"
#include "../widget/widget.hpp"

namespace ui
{

class Label : public virtual BaseWidget<>
{
public:
    explicit Label(const sf::String str_text = "", 
                    const sf::Font &font = res::default_font,
                    const sf::Color &color = sf::Color::Black,
                    unsigned int ch_size = 30,
                    OriginState state = OriginState::center,
                    bool with_splashes = false);
    
    explicit Label(sf::Text&& text,
                    const sf::Color &color = sf::Color::Black,
                    OriginState state = OriginState::center,
                    bool splashes = false);
    
    [[nodiscard]] sf::String      get_string() const;
    [[nodiscard]] unsigned int    get_char_size() const;
    [[nodiscard]] sf::Color       get_fill_color() const;
    bool empty();
    void clear();
    void append_string(sf::String &&str);
    void erase(std::size_t position, std::size_t count=1);
    void set_string(sf::String &&str);
    void set_origin_state(OriginState state) override;
    void set_char_size(unsigned int ch_size);
    void set_fill_color(sf::Color color);
    void update_origin();
    
    sf::FloatRect get_global_bounds() const override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    bool with_splashes = false;
private:
    std::vector<sf::Sprite> splashes;
    sf::Text text;
};

}