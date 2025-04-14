#include "LabelButton.hpp"

namespace ui
{

LabelButton::LabelButton(Label&& label,
                         callback_t on_press,
                         callback_t on_release) 
    : Label(label), on_press(on_press), on_release(on_release)
{}

void LabelButton::m_on_click(double delta_time)
{
    on_click();
}

void LabelButton::m_on_press([[maybe_unused]] double delta_time)
{
    on_press();
}

void LabelButton::m_on_release([[maybe_unused]] double delta_time)
{
    on_release();
}

void LabelButton::m_on_touch([[maybe_unused]] double delta_time)
{
    set_fill_color(color_touch);
}

void LabelButton::m_on_afk([[maybe_unused]] double delta_time)
{
    set_fill_color(color_afk);
    update_origin();
}

}