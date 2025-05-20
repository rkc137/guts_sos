#pragma once

#include <array>

#include "SceneManager.hpp"
#include "local_scenes/Curtain.hpp"
#include "../ui/label/stamp_label.hpp"
#include "levels/Level1.hpp"

class Intro : public SceneManager::Scene
{
public:
    Intro();
    ~Intro() = default;
    void update(double delta_time) override;
    void resize() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    const sf::Time pause = sf::seconds(1.3f);
    const sf::Time disappear_duration = sf::seconds(4);
    Curtain curtain{false, Curtain::ShowTypes::only_disappearnce, pause, pause, disappear_duration};
    sf::Clock clock;
    int volume = 100;
    bool text_done_check = false;
    bool done_check = false;
    std::vector<ui::StampLabel> texts;
    std::size_t active_text_iter = 0;
};