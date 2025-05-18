#pragma once

#include <array>

#include "SceneManager.hpp"
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
    sf::Clock clock;
    std::vector<ui::StampLabel> texts;
};