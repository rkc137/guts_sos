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
    // offset_angle = sf::degrees(std::clamp(offset_angle.asDegrees() - 1, 0.f, offset_angle.asDegrees()));
    offset_time = sf::seconds(std::clamp(offset_time.asSeconds() - 0.01f, 0.f, offset_time.asSeconds()));
    light.setRotation(
        (swaying_time_angle + offset_angle) * std::sin((clock.getElapsedTime() / (swaying_time - offset_time)) * 2 * std::numbers::pi)
    );
}

void BasementBackground::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(background, states);
    target.draw(light, states);
}
