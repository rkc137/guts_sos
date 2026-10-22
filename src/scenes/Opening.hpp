#pragma once

#include "../ui/label/label.hpp"
#include "SceneManager.hpp"
#include "MainMenu.hpp"
#include "local_scenes/Curtain.hpp"

class Opening : public SceneManager::Scene
{
public:
    Opening();
    void resize() override;
    void update(double delta_time) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    Curtain curtain;
    ui::Label author{scene_strings["author"], res::brutal_font, sf::Color::White};
    ui::Label made_with{scene_strings["madewith"], res::brutal_font, sf::Color::White};
};