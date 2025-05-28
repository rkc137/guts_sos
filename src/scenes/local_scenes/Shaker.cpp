#include "Shaker.hpp"

Shaker::Shaker(sf::Time shake_time, float in_power)
    : shake_time(shake_time), in_power(in_power), power(in_power)
{
}

void Shaker::resize()
{
    original_view = get_window().getView();
}

void Shaker::update(unused double delta_time)
{
    if(shake_time < clock.getElapsedTime())
        get_window().setView(original_view);
    else
    {
        sf::View shakeView = original_view;
        shakeView.move({
            (rand() % 2 == 0 ? 1 : -1) * power * (rand() % 100) / 100.0f,
            (rand() % 2 == 0 ? 1 : -1) * power * (rand() % 100) / 100.0f
        });
        get_window().setView(shakeView);
        power = in_power - in_power * (clock.getElapsedTime() / shake_time);
    }
}

void Shaker::draw(unused sf::RenderTarget& target,
                  unused sf::RenderStates states) const
{}

bool Shaker::is_done()
{
    return shake_time < clock.getElapsedTime();
}