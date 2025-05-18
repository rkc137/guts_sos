#include "Curtain.hpp"

Curtain::Curtain(bool should_wait_response,
                 ShowTypes show_type,
                 sf::Time uppear_duration,
                 sf::Time showing_duration,
                 sf::Time disapear_duration) 
  : should_wait_response(should_wait_response), 
    show_type(show_type),
    uppear_duration(uppear_duration),
    showing_duration(showing_duration),
    disappear_duration(disapear_duration)
{
    assert(uppear_duration != sf::Time::Zero);
    assert(disappear_duration != sf::Time::Zero);
    if(show_type == ShowTypes::only_disappearnce)
        state = States::disappearing;
    shape.setFillColor({0, 0, 0, static_cast<uint8_t>(alpha)});
}

void Curtain::resize()
{
    shape.setSize(sf::Vector2f(get_window().getSize()));
}

void Curtain::update(unused double delta_time)
{
    if(state == States::done) return;
    auto time = clock.getElapsedTime();
    
    switch(state)
    {
    case States::uppearing:
        alpha = std::clamp(255.f - (time / uppear_duration * 255.f), 0.f, 255.f);
        if(time > uppear_duration && alpha < 1.f)
        {
            clock.restart();
            if(show_type == ShowTypes::only_appearance)
                state = States::done;
            else
                state = States::showing;
        }
        break;
    case States::showing:
        if(should_wait_response ? !is_waiting : (time > showing_duration))
        {
            clock.restart();
            state = States::disappearing;
        }
        break;
    case States::disappearing:
        alpha = std::clamp(time / disappear_duration * 255.f, 0.f, 255.f);
        if(time > disappear_duration && alpha > 254.f)
        {
            state = States::done;
            on_exit.value_or([]{})();
        }
        break;
    case States::done:
        [[fallthrough]];
    default:
        throw std::runtime_error(std::string{"bad state of "} + typeid(this).name());
        break;
    }
    shape.setFillColor({0, 0, 0, static_cast<uint8_t>(alpha)});
}

bool Curtain::is_done()
{
    return state == States::done;
}

void Curtain::let_go(std::function<void()> on_end)
{
    on_exit = std::move(on_end);
    is_waiting = false;
}

void Curtain::start_clock()
{
    clock.restart();
}

void Curtain::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(shape, states);
}
