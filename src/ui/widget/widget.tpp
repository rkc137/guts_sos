#include "widget.hpp"

namespace ui
{

template <typename WWT>
BaseWidget<WWT>::BaseWidget()
{}

template <typename WWT>
void BaseWidget<WWT>::update(double delta_time)
{
    auto &window = this->get_window();

    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    sf::Vector2f mouse_world_pos = window.mapPixelToCoords(mouse_pos, window.getView()) - getPosition();


    if(get_global_bounds().contains(mouse_world_pos) || is_in_focus)
    {
        m_on_touch(delta_time);
        if(sf::Mouse::isButtonPressed(mouse_button) || (sf::Keyboard::isKeyPressed(enter) && is_in_focus))
        {
            is_clicked = true;
            m_on_press(delta_time);
        }
        else if(is_clicked)
        {
            is_clicked = false;
            m_on_release(delta_time);
        }
    }
    else
    {
        m_on_afk(delta_time);
        is_clicked = false;
    }
}

}