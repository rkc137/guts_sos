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

void Telegraph::AllwaysFocusButton::m_on_click(unused double delta_time)
{
    clock_since_press.restart();
    press_noise.play();
}

void Telegraph::AllwaysFocusButton::m_on_release(unused double delta_time)
{   
    auto signal = clock_since_press.getElapsedTime() >= dash_time;
    parent.letter_bits.push_back(signal);
    parent.input_label.append_string(signal ? L"—" : L"•");
    
    press_noise.stop();
    parent.last_press_clock.restart();
    parent.is_letter_said = false;
    parent.is_word_said = false;
}

bool Telegraph::AllwaysFocusButton::press_conditions()
{
    return is_in_focus && sf::Keyboard::isKeyPressed(key_button);
}

void Telegraph::update(unused double delta_time)
{
    button.update(delta_time);
    auto time = last_press_clock.getElapsedTime();
    //you searching them every fkg frame

    if(is_word_said) return;

    if(!is_letter_said && time > letter_time)
    {
        if(auto it = res::morse_codes.find(letter_bits); it != res::morse_codes.end())
        {
            if(auto letr = it->second; letr != '\b')
            {
                output_label.append_string({letr});
                is_mission_done = output_label.get_string() == mission_text;
            }
            else if(!output_label.empty())
                output_label.erase(output_label.get_string().getSize() - 1);
        }
        letter_bits.clear();
        input_label.clear();
        is_letter_said = true;
    }
    else if(time > word_time)
    {
        if(!output_label.empty())
            output_label.append_string(" ");
        is_word_said = true;
    }
}

void Telegraph::resize()
{
    auto ws = get_wsize<>();
    input_label.set_char_size(ws.y / 10);
    output_label.set_char_size(ws.y / 10);
    input_label.setPosition({
        ws.x / 4.f * 3.f,
        ws.y / 2.f
    });
    output_label.setPosition({
        ws.x / 4.f * 3.f,
        ws.y / 2.f + input_label.get_char_size() * 1.5f
    });
}

void Telegraph::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(output_label, states);
    target.draw(input_label, states);
}

no_discard bool Telegraph::misson_done() const
{
    return is_mission_done;
}


