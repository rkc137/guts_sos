#include "Sprite.hpp"

Sprite::Sprite(sf::Texture &texture, ui::OriginState origin_state)
    : sprite(texture)
{
    using ostate = ui::OriginState;
    const auto size = static_cast<sf::Vector2f>(sprite.getTexture().getSize());
    switch(origin_state)
    {
    case ostate::left_down:
        sprite.setOrigin({0, size.y});
    break;
    case ostate::right_down:
        sprite.setOrigin({size.x, size.y});
    break;
    case ostate::left_up:
        sprite.setOrigin({0, 0});
    break;
    case ostate::right_up:
        sprite.setOrigin({size.x, 0});
    break;
    case ostate::center:
        sprite.setOrigin(size / 2);
    break;
    default:
        throw std::runtime_error("bad origin state for Sprite");
    }
}

void Sprite::resize()
{
    const auto wsize = get_wsize<float>();
    const auto scale = res::get_scale(wsize);
    sprite.setScale(scale);
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
