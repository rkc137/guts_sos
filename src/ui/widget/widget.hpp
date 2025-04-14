#pragma once 

#include <SFML/Graphics.hpp>

#include "../../core/WindowWrap.hpp"

namespace ui
{

template <typename WWT = DefaultWindowWrap>
class BaseWidget : public sf::Drawable, public sf::Transformable, public WWT
{
public:
    BaseWidget();
    virtual ~BaseWidget() = default;
    void update(double delta_time);

    enum class OriginState
    {
        center,
        left_up,
        left_down
    };
    
protected:
    virtual void m_on_press([[maybe_unused]] double delta_time){};
    virtual void m_on_click([[maybe_unused]] double delta_time){};
    virtual void m_on_release([[maybe_unused]] double delta_time){};
    virtual void m_on_touch([[maybe_unused]] double delta_time){};
    virtual void m_on_afk([[maybe_unused]] double delta_time){};
    [[nodiscard]] virtual sf::FloatRect get_global_bounds() const = 0;
    OriginState origin_state;

    //TODO: multibale choise of buttons
    sf::Mouse::Button mouse_button = sf::Mouse::Button::Left;
    sf::Keyboard::Scan key_button = sf::Keyboard::Scan::Enter;
    
    // const sf::RenderWindow &window;
    bool is_in_focus = false;
protected:
    bool is_clicked = false;
};

}

#include "widget.tpp"