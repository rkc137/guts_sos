#pragma once

#include <SFML/System.hpp>

#include <vector>

#include "../Utils.hpp"

class PausebleClock
{
public:
    PausebleClock() = default;
    void start();
    void pause();
    void resume();
    void restart();
    no_discard sf::Time get_elapsed_time() const;

private:
    sf::Clock clock;
    bool is_paused = false;
    sf::Time paused_time = sf::Time::Zero;
};

class SceneClock : public PausebleClock
{
public:
    SceneClock();
    static void set_pause_all(bool is_pause);

private:
    inline static std::vector<std::reference_wrapper<PausebleClock>> clocks;
};