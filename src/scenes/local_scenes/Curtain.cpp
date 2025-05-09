#include "Curtain.hpp"

Curtain::Curtain(bool is_quiting_on_time,
                 sf::Time uppear_duration,
                 sf::Time showing_duration,
                 sf::Time disapear_duration) 
  : is_quiting_on_time(is_quiting_on_time), 
    uppear_duration(uppear_duration),
    showing_duration(showing_duration),
    disappear_duration(disapear_duration)
{
    assert(uppear_duration != sf::Time::Zero);
    assert(disappear_duration != sf::Time::Zero);
}

void Curtain::resize()
{
    shape.setSize(sf::Vector2f(get_window().getSize()));
}

void Curtain::update(unused double delta_time)
{
    if(state == done) return;
    auto time = clock.getElapsedTime();
    
    switch(state)
    {
    case uppearing:
        alpha = std::clamp(255.f - (time / uppear_duration * 255.f), 0.f, 255.f);
        if(time > uppear_duration && alpha < 1.f)
        {
            clock.restart();
            state = showing;
        }
        break;
    case showing:
        if(time > showing_duration)
        {
            clock.restart();
            state = disappearing;
        }
        break;
    case disappearing:
        alpha = std::clamp(time / disappear_duration * 255.f, 0.f, 255.f);
        if(time > disappear_duration && alpha > 254.f)
            state = done;
        break;
    case done:
        [[fallthrough]];
    default:
        throw std::runtime_error(std::string{"bad state of "} + typeid(this).name() );
        break;
    }
    shape.setFillColor({0, 0, 0, static_cast<uint8_t>(alpha)});
}

bool Curtain::is_done()
{
    return state == done;
}

void Curtain::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(shape, states);
}
