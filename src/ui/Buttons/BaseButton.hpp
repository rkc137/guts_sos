#pragma once

#include <functional>

#include "../widget/widget.hpp"

namespace ui
{

class BaseButton : public virtual BaseWidget<>
{
public:
    void update(double delta_time) override;

protected:
    virtual void m_on_press(unused double delta_time){};
    virtual void m_on_click(unused double delta_time){};
    virtual void m_on_release(unused double delta_time){};
    virtual void m_on_touch(unused double delta_time){};
    virtual void m_on_afk(unused double delta_time){};
    virtual bool press_conditions();

    bool is_clicked = false;
    
    //TODO: multibale choise of buttons
    sf::Mouse::Button mouse_button = sf::Mouse::Button::Left;
    sf::Keyboard::Scan key_button = sf::Keyboard::Scan::Enter;
};

}