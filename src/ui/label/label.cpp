#include "label.hpp"

namespace ui
{

Label::Label(const sf::String str_text, 
            const sf::Font &font,
            const sf::Color &color,
            unsigned int ch_size,
            OriginState state)
            : Label({font, str_text, ch_size}, color, state)
{}

Label::Label(sf::Text &&text, const sf::Color &color, OriginState state)
    : text(text)
{
    origin_state = state;
    text.setFillColor(color);
    update_origin();
    text.setPosition({0, 0});
}

void Label::set_string(sf::String &&str)
{
    text.setString(std::move(str));
    update_origin();
}

sf::String Label::get_string() const
{
    return text.getString();
}

void Label::set_origin_state(OriginState state)
{
    origin_state = state;
    update_origin();
}

ui::OriginState Label::get_origin_state() const
{
    return origin_state;
}

void Label::set_char_size(unsigned int ch_size)
{
    text.setCharacterSize(ch_size);
    update_origin();
}

unsigned int Label::get_char_size() const
{
    return text.getCharacterSize();
}

void Label::set_fill_color(sf::Color color)
{
    text.setFillColor(color);
}

sf::Color Label::get_fill_color() const
{
    return text.getFillColor();
}

bool Label::empty()
{
    return text.getString().isEmpty();
}

void Label::clear()
{
    set_string({});
}

void Label::append_string(sf::String &&str)
{
    set_string(get_string() + str);
}

void Label::erase(std::size_t position, std::size_t count)
{
    auto s = get_string();
    s.erase(position, count);
    set_string(std::move(s));
}

void Label::update_origin()
{
    sf::FloatRect text_rect = text.getLocalBounds();
    auto pos = text_rect.position;
    auto size = text_rect.size;
    switch(origin_state)
    {
    case OriginState::center:
        text.setOrigin({
            pos.x + size.x / 2.0f,
            pos.y + size.y / 2.0f
        });
        break;
    case OriginState::left_up:
        text.setOrigin({
            pos.x,
            pos.y
        });
        break;
    case OriginState::left_down:
        text.setOrigin({
            pos.x,
            pos.y + size.y
        });
        break;
    default:
        throw std::runtime_error("bad origin state");
        break;
    }
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