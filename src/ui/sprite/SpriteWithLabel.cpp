#include "SpriteWithLabel.hpp"

namespace ui
{

void SpriteWithLabel::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite, states);
    target.draw(label, states);
}

sf::FloatRect SpriteWithLabel::get_global_bounds() const
{
    return sprite.get_global_bounds();
}

void SpriteWithLabel::resize()
{
    sprite.resize();
    auto wsize = get_wsize<float>();
    auto [bpos, bsize] = sprite.get_global_bounds();
    label.set_char_size(wsize.y / size_coefficient);
    
    sf::Vector2f pos;
    switch(label.get_origin_state())
    {
    case ui::OriginState::left_up:
        switch(sprite.get_origin_state())
        {
        case ui::OriginState::left_down:
            pos = {bsize.x / 10, -bsize.y + bsize.y / 10};
        break;
        case ui::OriginState::right_up:
            pos = {bsize.x / 10 - bsize.x, bsize.y / 10};
        break;
        default:
            throw std::runtime_error("not supported state");
        }
    break;
    case ui::OriginState::left_down:
        pos = {(-bsize.x / 15) * 14, -(-bsize.y + bsize.y / 10)};
    break;
    default:
        throw std::runtime_error("not supported state");
    }
    label.setPosition(pos);
}

SpriteWithLabel::SpriteWithLabel(sf::String text, ui::OriginState text_state, Sprite &&sprite, int size_cf = 21) :
    label{
        text,
        res::too_much_ink,
        sf::Color::White
    },
    sprite{std::move(sprite)},
    size_coefficient{size_cf}
{
    label.set_origin_state(text_state);
}

}