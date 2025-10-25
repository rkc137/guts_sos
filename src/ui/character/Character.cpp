#include "Character.hpp"

namespace ui
{

Character::Character(
    res::Texture &texture,
    ui::OriginState origin_state,
    std::vector<sf::String> phrases,
    sf::Time pause_after_talk,
    sf::Time appear_time) 
    : origin_state(origin_state),
      phrases(phrases),
      pause_after_talk(pause_after_talk),
      label{
        ui::Label{
            L"", res::too_much_ink,
            sf::Color::White
        },
        phrases.front(),
        res::voice,
        sf::seconds(0.08)
      },
      sprite(texture, origin_state),
      appear_time(appear_time)
{
    label.with_splashes = true;
}

void Character::set_pheases(std::vector<sf::String> &&new_phrases)
{
    phrases = std::move(new_phrases);
    phrases_iter = 0;
}

void Character::resize()
{
    const auto wsize = get_wsize<float>();

    label.set_char_size(wsize.y / 20);
    label.setPosition(wsize / 2);
    sprite.resize();

    const auto sizex = get_global_bounds().size.x;
    switch (origin_state)
    {
    case ui::OriginState::left_down:
        setPosition({0, wsize.y});
        anim_poses = {-sizex, 0};
    break;
    case ui::OriginState::right_down:
        setPosition(wsize);
        anim_poses = {wsize.x + sizex, wsize.x};
    break;
    default:
        throw std::runtime_error("bad origin state");
    }
}

bool Character::is_end_of_speech() const
{
    return is_end && animation_clock.get_elapsed_time() >= appear_time;
}

void Character::update(double delta_time)
{
    const auto wsize = get_wsize<float>();

    if(!is_appear)
    {
        setPosition({
            anim::interpolate<anim::ease_out_cubic>(
                anim_poses,
                animation_clock.get_elapsed_time(), appear_time),
            wsize.y
        });
        is_appear = animation_clock.get_elapsed_time() >= appear_time;
    }
    else if(is_end)
    {
        setPosition({
            anim::interpolate<anim::ease_out_cubic>(
                {anim_poses.second, anim_poses.first},
                animation_clock.get_elapsed_time(), appear_time),
            wsize.y
        });
        return;
    }

    label.update(delta_time);
    
    if(label.is_done() && label.last_stamp() >= pause_after_talk)
    {
        is_end = ++phrases_iter >= phrases.size();
        if(is_end)
            animation_clock.restart();
        else
            label.reset_text(phrases[phrases_iter]);
    }    
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    auto transform = states.transform;
    states.transform *= getTransform();
    target.draw(sprite, states);
    states.transform = transform;
    if(!is_end)
        target.draw(label, states);
}

sf::FloatRect Character::get_global_bounds() const
{
    return sprite.get_global_bounds();
}

}