#pragma once

#include "SceneManager.hpp"
#include "../ui/label/label.hpp"
#include "../ui/Buttons/LabelButton.hpp"
#include "local_scenes/Telegraph.hpp"

class MainMenu : public SceneManager::Scene
{
public:
    explicit MainMenu();
    ~MainMenu() = default;
    void update(double delta_time) override;
    void resize() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    Telegraph telegraph;
    ui::Label logo{res::app_name, res::cybersomething, sf::Color::White, 100};
    ui::LabelButton start{ui::Label{L"start", res::cybersomething, sf::Color::White, 50}};
    ui::LabelButton exit{ui::Label{L"exit", res::cybersomething, sf::Color::White, 50}};

    // Label buttons_codes{res::default_font, L"•••\n———\n•", 50, sf::Color::Black};
    // sf::Sprite blocknote{res::blocknote};
};