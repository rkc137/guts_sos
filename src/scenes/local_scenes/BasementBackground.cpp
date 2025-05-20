#include "BasementBackground.hpp"

BasementBackground::BasementBackground()
{
    background.setOrigin(static_cast<sf::Vector2f>(res::bunker.getSize() / 2));
}

void BasementBackground::resize()
{
    auto wsize = get_wsize<float>();
    auto bgsize = static_cast<sf::Vector2f>(res::bunker.getSize());
    auto bgscale = std::max(
        std::abs(wsize.x / bgsize.x),
        std::abs(wsize.y / bgsize.y)
    );
    background.setPosition(wsize / 2);
    background.setScale({bgscale, bgscale});
}

void BasementBackground::update(unused double delta_time)
{

}

void BasementBackground::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(background, states);
}
