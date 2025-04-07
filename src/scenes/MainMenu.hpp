#pragma once

#include "SceneManager.hpp"
#include "../Logger/Logger.hpp"
#include "../ui/label/label.hpp"
#include "../ui/Buttons/LabelButton.hpp"

class MainMenu : public SceneManager::Scene
{
public:
    explicit MainMenu();
    ~MainMenu() = default;
    void update(double delta_time) override;
    void resize() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    sf::View main_view;

    sf::CircleShape shape{50.f};

    ui::Label logo{res::app_name, res::cybersomething, sf::Color::White, 100};
    ui::LabelButton start{ui::Label{"start"s, res::cybersomething, sf::Color::White, 50}};
    ui::LabelButton exit{ui::Label{"exit"s, res::cybersomething, sf::Color::White, 50}};

    // Label buttons{res::cybersomething, L"start\noptions\nexit", 50, sf::Color::Black};
    // Label buttons_codes{res::default_font, L"•••\n———\n•", 50, sf::Color::Black};
    // Label author{res::cybersomething, L"made by rkc137", 50, sf::Color::Black};
    // sf::Sprite blocknote{res::blocknote};

};