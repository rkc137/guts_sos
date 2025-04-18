#pragma once

#include "SceneManager.hpp"
#include "local_scenes/Curtain.hpp"
#include "../ui/label/label.hpp"

class Opening : public SceneManager::Scene
{
public:
    void resize() override;
    void update(double delta_time) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    Curtain curtain;
    ui::Label author{L"made by rkc137", res::cybersomething, sf::Color::White};
    ui::Label made_with{L"made with sfml", res::cybersomething, sf::Color::White};
};