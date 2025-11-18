#include "Sprite.hpp"

Sprite::Sprite(sf::Texture &texture, ui::OriginState origin_state)
    : sprite(texture)
{
    using ostate = ui::OriginState;
    const auto size = static_cast<sf::Vector2f>(texture.getSize());
    this->origin_state = origin_state;

    sf::Vector2f origin;
    switch(origin_state)
    {
    case ostate::left_down:
        origin = {0, size.y};
    break;
    case ostate::right_down:
        origin = {size.x, size.y};
    break;
    case ostate::left_up:
        origin = {};
    break;
    case ostate::right_up:
        origin = {size.x, 0};
    break;
    case ostate::center:
        origin = size / 2;
    break;
    default:
        throw std::runtime_error("bad origin state for Sprite");
    }
    sprite.setOrigin(origin);
}

void Sprite::resize()
{
    sprite.setScale(res::get_adaptive_scale(
        get_wsize(),
        sprite.getTexture().getSize()
    ));
}

void Sprite::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite, states);
}

sf::FloatRect Sprite::get_global_bounds() const
{
    auto rect = sprite.getGlobalBounds();
    return {
        rect.position * getScale(),
        rect.size * getScale()
    };
}
