#pragma once 

#include <SFML/Graphics.hpp>

namespace ui
{

class WindowWrap
{
protected:
    static sf::RenderWindow &window;
private:
    inline static sf::RenderWindow *m_window = nullptr; 
};

template <typename WindowWrap>
class BaseWidget : protected WindowWrap
{
public:

};


class Widget : public sf::Drawable, public sf::Transformable
{
public:
    Widget(const sf::RenderWindow &window);
    virtual ~Widget() = default;

    void update(double delta_time);

protected:
    virtual void m_on_press(double delta_time){};
    virtual void m_on_release(double delta_time){};
    virtual void m_on_touch(double delta_time){};
    virtual void m_on_afk(double delta_time){};
    virtual sf::FloatRect get_global_bounds() const = 0;

    sf::Mouse::Button mouse_button = sf::Mouse::Button::Left;
    sf::Keyboard::Key enter = sf::Keyboard::Key::Enter;
    
    const sf::RenderWindow &window;
    bool is_in_focus = false;
    bool is_clicked = false;
};

}