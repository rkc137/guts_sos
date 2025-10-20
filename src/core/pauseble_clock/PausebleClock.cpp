#include "PausebleClock.hpp"

void PausebleClock::start()
{
    restart();
}

void PausebleClock::pause()
{
    if(is_paused) return;
    paused_time = clock.getElapsedTime();
    is_paused = true;
}

void PausebleClock::resume()
{
    if(!is_paused) return;
    clock.restart();
    is_paused = false;
}

sf::Time PausebleClock::getElapsedTime() const 
{
    if(is_paused) return paused_time;
    return paused_time + clock.getElapsedTime();
}

void PausebleClock::restart()
{
    clock.restart();
    is_paused = false;
    paused_time = sf::Time::Zero;
}

SceneClock::SceneClock()
{
    clocks.emplace_back(*this);
}

void SceneClock::set_pause_all(bool is_pause)
{
    if(is_pause)
        for(auto &c : clocks)
            c.get().pause();
    else
        for(auto &c : clocks)
            c.get().resume();
}