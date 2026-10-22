#pragma once

#include "../ui/Buttons/LabelButton.hpp"
#include "SceneManager.hpp"

class ChooseLang : public SceneManager::Scene
{
public:
    ChooseLang();
    void resize() override;
    void update(double delta_time) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    ui::LabelButton rus{ui::Label{L"русский", res::brutal_font.fonts[res::Lang::rus], sf::Color::White, 50}};
    ui::LabelButton eng{ui::Label{L"english", res::brutal_font.fonts[res::Lang::eng], sf::Color::White, 50}};
};
