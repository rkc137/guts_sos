#include "BasementBackground.hpp"

BasementBackground::BasementBackground()
{
    background.setOrigin(static_cast<sf::Vector2f>(res::bunker.getSize() / 2));
    light.setOrigin({static_cast<float>(res::light.getSize().x) / 2, 0});
}

void BasementBackground::resize()
{
    const auto wsize = get_wsize<float>();
    const auto scale = res::get_scale(wsize);
     
    background.setPosition(wsize / 2);
    background.setScale(scale);
    light.setPosition({wsize.x / 2, -wsize.y * 1.25f});
    light.setScale(scale);
}

void BasementBackground::update(unused double delta_time)
{
    light.setRotation(
        swaying_time_angle * std::sin((clock.getElapsedTime() / swaying_time) * 2 * M_PI)
    );
}

void BasementBackground::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(background, states);
    target.draw(light, states);
}
