#pragma once

#include <functional>

#include "../label/label.hpp"

namespace ui
{

class Label_button : public Label
{
public:
    explicit Label_button(Label&& label);
    
    std::function<void()> on_press = [](){};
    std::function<void()> on_release = [](){};

protected:
    void m_on_press(double delta_time) override;
    void m_on_release(double delta_time) override;
    void m_on_touch(double delta_time) override;
    void m_on_afk(double delta_time) override;

    sf::Color color_afk = text.getFillColor();
    sf::Color color_touch = sf::Color::Red;
};


}