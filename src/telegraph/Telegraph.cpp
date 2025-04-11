#include "Telegraph.hpp"

Telegraph::Telegraph()
{
}

Telegraph::AllwaysFocusButton::AllwaysFocusButton()
    : ui::LabelButton{ui::Label{}} 
{
    key_button = sf::Keyboard::Scancode::Space;
    is_in_focus = true;
    on_press = [&](){
    };
}

void Telegraph::update([[maybe_unused]] double delta_time)
{
}

void Telegraph::resize()
{
    auto ws = get_window().getSize();
    input.set_char_size(ws.y / 10);
    output.set_char_size(ws.y / 10);
    input.setPosition({
        ws.x / 2.f,
        ws.y / 2.f
    });
    output.setPosition({
        ws.x / 2.f,
        ws.y / 2.f + input.get_global_bounds().size.y * 1.5f
    });
}

void Telegraph::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(input, states);
    target.draw(output, states);
}


