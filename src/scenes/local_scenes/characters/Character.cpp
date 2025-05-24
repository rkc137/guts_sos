#include "Character.hpp"

Character::Character(res::Texture &texture, ui::OriginState origin_state, sf::String phrase) 
    : sprite(texture),
      origin_state(origin_state),
      phrase{ui::Label{L"", res::too_much_ink, sf::Color::White}, phrase, res::voice}
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

    phrase.set_char_size(wsize.y / 20); 
    phrase.setPosition(wsize / 2);

    using ui::OriginState;
    if(origin_state == OriginState::left_down)
        sprite.setPosition({0, wsize.y});
    else if(origin_state == OriginState::right_down)
        sprite.setPosition(wsize);
    else 
        throw std::runtime_error("bad origin state for character");
    sprite.setScale(scale);
}

void Character::update(double delta_time)
{
    phrase.update(delta_time);
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
    target.draw(phrase, states);
}