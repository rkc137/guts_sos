#include "BaseButton.hpp"

namespace ui
{

void BaseButton::update(double delta_time)
{
    auto &window = this->get_window();

    sf::Vector2f mouse_world_pos =
        window.mapPixelToCoords(
            sf::Mouse::getPosition(window),
            window.getView()
        ) - getPosition();

    if(get_global_bounds().contains(mouse_world_pos) || is_in_focus)
    {
        m_on_touch(delta_time);
        if(press_conditions())
        {
            if(!is_clicked)
                m_on_click(delta_time);
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

bool BaseButton::press_conditions()
{
    return sf::Mouse::isButtonPressed(mouse_button)
            || (sf::Keyboard::isKeyPressed(key_button) && is_in_focus);
}

}