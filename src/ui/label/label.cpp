#include "label.hpp"

namespace ui
{

Label::Label(const sf::String str_text, 
            const sf::Font &font,
            const sf::Color &color,
            unsigned int ch_size,
            OriginState state,
            bool with_splashes)
            : Label({font, str_text, ch_size}, color, state, with_splashes)
{}

Label::Label(sf::Text &&text, const sf::Color &color, OriginState state, bool splashes)
    : text(text)
{
    origin_state = state;
    with_splashes = splashes;
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
    static auto random_float = [](float a, float b) -> float {
        float random = ((float) rand()) / (float)RAND_MAX;
        float diff = b - a;
        float r = random * diff;
        return a + r;
    };

    states.transform *= getTransform();
    if(with_splashes)
    {
        int length = get_string().getSize();
        auto b = get_global_bounds();
        for(int i = 0; i < length  * 2; i++)
        {
            sf::Sprite splash{res::splash};
            sf::Vector2f size{res::splash.frame_size};
            splash.setOrigin(size / 2.f);
            splash.setScale(res::get_adaptive_scale(get_wsize<float>(), size));
            splash.setRotation(sf::degrees(rand() % 360));
            splash.setPosition({
                random_float(0, b.size.x) - (b.size.x / 2),
                random_float(0, b.size.y) - (b.size.y / 2)
            });
            target.draw(splash, states);
        }
    }
    target.draw(text, states);
}

sf::FloatRect Label::get_global_bounds() const
{
    // return getTransform().transformRect(text.getGlobalBounds());
    return text.getGlobalBounds();
}

}