#pragma once

#include "../SceneManager.hpp"
#include <functional>

class Curtain : public SceneManager::Scene
{
public:
    enum class ShowTypes
    {
        all,
        only_appearance,
        only_disappearnce
    };
    Curtain(bool should_waiting_response = false,
            ShowTypes show_type = ShowTypes::all,
            sf::Time uppear_duration = sf::seconds(2),
            sf::Time showing_duration = sf::seconds(3),
            sf::Time disappear_duration = sf::seconds(1.5));
    void update(double delta_time) override;
    void resize() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void let_go(std::function<void()> on_end);
    void start_clock();
    no_discard bool is_done();
private:
    enum class States
    {
        uppearing,
        showing,
        disappearing,
        done
    } state = States::uppearing;

    float alpha = 0;
    bool is_waiting = true;
    bool should_wait_response;
    ShowTypes show_type;
    std::optional<std::function<void()>> on_exit;
    sf::Time uppear_duration;
    sf::Time showing_duration;
    sf::Time disappear_duration;
    sf::RectangleShape shape;
    sf::Clock clock;
};