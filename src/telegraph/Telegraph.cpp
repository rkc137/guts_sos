#include "Telegraph.hpp"

Telegraph::Telegraph() : button(*this)
{
}

Telegraph::AllwaysFocusButton::AllwaysFocusButton(Telegraph &parent)
    : parent(parent)
{
    key_button = sf::Keyboard::Scancode::Space;
    is_in_focus = true;
    press_noise.setLooping(true);
}

void Telegraph::AllwaysFocusButton::m_on_click([[maybe_unused]] double delta_time)
{
    clock_since_press.restart();
    press_noise.play();
}

void Telegraph::AllwaysFocusButton::m_on_release([[maybe_unused]] double delta_time)
{
    auto time_since_press = clock_since_press.getElapsedTime();
    press_noise.stop();
    
    auto signal = time_since_press < dash_time;
    parent.letter_bits.push_back(signal);
    parent.input_label.append_string(signal ? L"•" : L"—");
    parent.input_label.update_origin();
    last_press_clock.restart();
}

bool Telegraph::AllwaysFocusButton::press_conditions()
{
    return is_in_focus && sf::Keyboard::isKeyPressed(key_button);
}

void Telegraph::update([[maybe_unused]] double delta_time)
{
    button.update(delta_time);
}

void Telegraph::resize()
{
    auto ws = get_window().getSize();
    input_label.set_char_size(ws.y / 10);
    output_label.set_char_size(ws.y / 10);
    input_label.setPosition({
        ws.x / 2.f,
        ws.y / 2.f
    });
    output_label.setPosition({
        ws.x / 2.f,
        ws.y / 2.f + input_label.get_global_bounds().size.y * 1.5f
    });
}

void Telegraph::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(input_label, states);
    target.draw(output_label, states);
}


