#pragma once 

#include <SFML/Graphics.hpp>

namespace ui
{

class DefaultWindowWrap
{
public:
    static void set_window_wrap_ptr(sf::RenderWindow *window) { win = window; }
protected:
    static sf::RenderWindow& get_window() { return *win; }
private:
    inline static sf::RenderWindow *win = nullptr; 
};

template <typename WWT>
class BaseWidget : public sf::Drawable, public sf::Transformable, public WWT
{
public:
    BaseWidget();
    virtual ~BaseWidget() = default;

    void update(double delta_time);

protected:
    virtual void m_on_press([[maybe_unused]] double delta_time){};
    virtual void m_on_release([[maybe_unused]] double delta_time){};
    virtual void m_on_touch([[maybe_unused]] double delta_time){};
    virtual void m_on_afk([[maybe_unused]] double delta_time){};
    virtual sf::FloatRect get_global_bounds() const = 0;

    sf::Mouse::Button mouse_button = sf::Mouse::Button::Left;
    sf::Keyboard::Key enter = sf::Keyboard::Key::Enter;
    
    // const sf::RenderWindow &window;
    bool is_in_focus = false;
    bool is_clicked = false;
};

using Widget = BaseWidget<DefaultWindowWrap>;

}

#include "widget.tpp"