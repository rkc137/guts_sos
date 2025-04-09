#pragma once

#include <SFML/Window.hpp>

#include "../scenes/SceneManager.hpp"
#include "../ui/label/label.hpp"
#include "../ui/Buttons/LabelButton.hpp"

class Telegraph : public SceneManager::Scene
{
public:
    Telegraph();
    void update(double delta_time) override;
    void resize() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    ui::Label input{L"1___1", res::cybersomething, sf::Color::White, 80, ui::Label::OriginState::center};//••—•——
    ui::Label output{input};//text
private:
    sf::Time dash_time = sf::seconds(0.25);
    sf::Time letter_time = sf::seconds(1.70);
    sf::Time word_time = sf::seconds(2);
    
    class AllwaysFocusButton : public ui::LabelButton
    {
    public: 
        AllwaysFocusButton();
    } button;
};