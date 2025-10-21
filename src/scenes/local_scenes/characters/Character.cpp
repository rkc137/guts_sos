#include "Character.hpp"

Character::Character(
    res::Texture &texture,
    ui::OriginState origin_state,
    std::vector<sf::String> phrases,
    sf::Time pause_after_talk) 
    : sprite(texture),
      origin_state(origin_state),
      phrases(phrases),
      label{
        ui::Label{
            L"", res::too_much_ink,
            sf::Color::White
        },
        phrases.front(),
        res::voice,
        sf::seconds(0.08)
      },
      pause_after_talk(pause_after_talk)
{
    label.with_splashes = true;
    using ui::OriginState;
    if(origin_state == OriginState::left_down)
        sprite.setOrigin({0, static_cast<float>(texture.getSize().y)});
    else if(origin_state == OriginState::right_down)
        sprite.setOrigin(static_cast<sf::Vector2f>(texture.getSize()));
    else 
        throw std::runtime_error("bad origin state for character");
}

void Character::set_pheases(std::vector<sf::String> &&new_phrases)
{
    phrases = std::move(new_phrases);
    phrases_iter = 0;
}

void Character::resize()
{
    const auto wsize = get_wsize<float>();
    const auto scale = res::get_scale(wsize);

    label.set_char_size(wsize.y / 20);
    label.setPosition(wsize / 2);

    using ui::OriginState;
    if(origin_state == OriginState::left_down)
        sprite.setPosition({0, wsize.y}); 
    else if(origin_state == OriginState::right_down)
        sprite.setPosition(wsize);
    else 
        throw std::runtime_error("bad origin state for character");
    sprite.setScale(scale);
}

bool Character::is_end_of_speech() const
{
    return is_end;
}

void Character::update(double delta_time)
{
    if(is_end)
        return;
    
    label.update(delta_time);
    
    if(label.is_done() && label.last_stamp() >= pause_after_talk)
    {
        is_end = ++phrases_iter >= phrases.size();
        if(is_end)
            return;
        label.reset_text(phrases[phrases_iter]);
    }    
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
    target.draw(label, states);
}
