#include "label.hpp"

namespace ui
{

Label::Label(const sf::String str_text, 
            const sf::Font &font,
            const sf::Color &color,
            unsigned int ch_size)
            : Label({font, str_text, ch_size}, color)
{}

Label::Label(sf::Text &&text, const sf::Color &color)
    : text(text)
{
    text.setFillColor(color);
    update_origin();
    text.setPosition({0, 0});
}

void Label::set_char_size(unsigned int ch_size)
{
    text.setCharacterSize(ch_size);
    update_origin();
}

unsigned int Label::get_char_size()
{
    return text.getCharacterSize();
}

void Label::set_fill_color(sf::Color color)
{
    text.setFillColor(color);
}

sf::Color Label::get_fill_color()
{
    return text.getFillColor();
}

void Label::update_origin()
{
    sf::FloatRect text_rect = text.getLocalBounds();
    auto pos = text_rect.position;
    auto size = text_rect.size;
    text.setOrigin({
        pos.x + size.x / 2.0f,
        pos.y + size.y / 2.0f
    });
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(text, states);
}

sf::FloatRect Label::get_global_bounds() const
{
    // return getTransform().transformRect(text.getGlobalBounds());
    return text.getGlobalBounds();
}

}