#pragma once

#include <array>

#include "SceneManager.hpp"
#include "local_scenes/Curtain.hpp"
#include "../ui/label/stamp_label.hpp"

class Intro : public SceneManager::Scene
{
public:
    Intro();
    ~Intro() = default;
    void update(double delta_time) override;
    void resize() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    Curtain curtain{false, Curtain::ShowTypes::only_disappearnce};
    sf::Clock clock;
    sf::Time pause = sf::seconds(1.3f);
    bool text_done_check = false;
    bool done_check = false;
    std::vector<ui::StampLabel> texts;
    std::size_t active_text_iter = 0;
};