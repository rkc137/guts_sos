#pragma once

#include <SFML/Window.hpp>

#include "../logger/Logger.hpp"

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
    ui::Label input_label{L"1___1", res::cybersomething, sf::Color::White, 80, ui::Label::OriginState::center};//••—•——
    ui::Label output_label{input_label};//text
    sf::String input;
    sf::String output;
private:
    inline static const sf::Time dash_time = sf::seconds(0.25);
    inline static const sf::Time letter_time = sf::seconds(1.70);
    inline static const sf::Time word_time = sf::seconds(2);
    
    class AllwaysFocusButton : public ui::LabelButton
    {
    public: 
        AllwaysFocusButton(Telegraph &parent);
        sf::Sound press_noise{res::morse_noise};
        sf::Clock clock_since_press;
        // sf::Clock last_press_clock;
        Telegraph &parent;
    } button;
};