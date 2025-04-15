#pragma once

#include <functional>

#include "../label/label.hpp"

namespace ui
{

class LabelButton : public Label
{
public:
    using callback_t = std::function<void()>;//should be void(delta)
    
    explicit LabelButton(Label&& label,
                         callback_t on_press = [](){},
                         callback_t on_release = [](){});
    
    callback_t on_press = [](){};
    callback_t on_release = [](){};
    callback_t on_click = [](){};
protected:
    void m_on_click(double delta_time) override;
    void m_on_press(double delta_time) override;
    void m_on_release(double delta_time) override;
    void m_on_touch(double delta_time) override;
    void m_on_afk(double delta_time) override;

    sf::Color color_afk = get_fill_color();
    sf::Color color_touch = sf::Color::Red;
};

}