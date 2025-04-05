#include "label_button.hpp"

namespace ui
{

Label_button::Label_button(Label&& label) : Label(label)
{}

void Label_button::m_on_press(double delta_time)
{
    on_press();
}

void Label_button::m_on_release(double delta_time)
{
    on_release();
}

void Label_button::m_on_touch(double delta_time)
{
    text.setFillColor(color_touch);
}

void Label_button::m_on_afk(double delta_time)
{
    text.setFillColor(color_afk);
    update_origin();
}


}