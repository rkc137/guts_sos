#pragma once

#include <functional>

#include "../widget/widget.hpp"

namespace ui
{

class BaseButton : public virtual BaseWidget<>
{
public:
    void update(double delta_time) override;

private:
    virtual void m_on_press([[maybe_unused]] double delta_time){};
    virtual void m_on_click([[maybe_unused]] double delta_time){};
    virtual void m_on_release([[maybe_unused]] double delta_time){};
    virtual void m_on_touch([[maybe_unused]] double delta_time){};
    virtual void m_on_afk([[maybe_unused]] double delta_time){};

protected:
    bool is_clicked = false;
    
    //TODO: multibale choise of buttons
    sf::Mouse::Button mouse_button = sf::Mouse::Button::Left;
    sf::Keyboard::Scan key_button = sf::Keyboard::Scan::Enter;
};

}