#pragma once

#include "SceneManager.hpp"
#include "../Logger/Logger.hpp"
#include "../ui/label/label.hpp"

class MainMenu : public SceneManager::Scene
{
public:
    explicit MainMenu();
    ~MainMenu();
    void update(double delta_time) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    sf::View main_view;

    sf::CircleShape shape{50.f};

    ui::Label logo{res::app_name, sf::Color::White, 80, res::cybersomething};//{res::cybersomething, res::app_name, 80, sf::Color::Black};
    
    // sf::Text
    // ui::Label logo{res::cybersomething, res::app_name, 80, sf::Color::Black};
    // Label buttons{res::cybersomething, L"start\noptions\nexit", 50, sf::Color::Black};
    // Label buttons_codes{res::default_font, L"•••\n———\n•", 50, sf::Color::Black};
    // Label author{res::cybersomething, L"made by rkc137", 50, sf::Color::Black};
    // sf::Sprite blocknote{res::blocknote};

};