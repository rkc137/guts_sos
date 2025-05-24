#include "Character.hpp"

Character::Character(res::Texture &texture, ui::OriginState origin_state) 
    : sprite(texture), origin_state(origin_state)
{
    using ui::OriginState;
    if(origin_state == OriginState::left_down)
        sprite.setOrigin({0, static_cast<float>(texture.getSize().y)});
    else if(origin_state == OriginState::right_down)
        sprite.setOrigin(static_cast<sf::Vector2f>(texture.getSize()));
    else 
        throw std::runtime_error("bad origin state for character");
}

void Character::resize()
{
    const auto wsize = get_wsize<float>();
    const auto scale = res::get_scale(wsize);
    using ui::OriginState;
    if(origin_state == OriginState::left_down)
        sprite.setPosition({0, wsize.y});
    else if(origin_state == OriginState::right_down)
        sprite.setPosition(wsize);
    else 
        throw std::runtime_error("bad origin state for character");
    sprite.setScale(scale);
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}