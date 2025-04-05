#include "label.hpp"

namespace ui
{

Label::Label(const sf::RenderWindow &window,
            const std::string str_text, 
            const sf::Color &color,
            int ch_size,
            const sf::Font &font)
            : Widget(window), text(str_text, font, ch_size)
{
    text.setFillColor(color);
    update_origin();
    text.setPosition({0, 0});
}

void Label::update_origin()
{
    sf::FloatRect text_rect = text.getLocalBounds();
    auto pos = text_rect.position;
    auto size = text_rect.size;
    text.setOrigin(pos.x + size.x / 2.0f,
                   pos.y  + size.y / 2.0f);
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