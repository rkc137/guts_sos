#pragma once

#include <SFML/Window.hpp>

#include <vector>

#include "../SceneManager.hpp"
#include "../../ui/label/label.hpp"
#include "../../ui/Buttons/BaseButton.hpp"

class Telegraph : public SceneManager::Scene
{
public:
    Telegraph();
    void update(double delta_time) override;
    void resize() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    ui::Label input_label{L"", res::default_font, sf::Color::White, 80, ui::OriginState::center, true};//••—•——
    ui::Label output_label{L"", res::cybersomething, sf::Color::White, 80, ui::OriginState::center, true};//text
private:
    inline static const sf::Time dash_time = sf::seconds(0.25);
    inline static const sf::Time letter_time = sf::seconds(1.70);
    inline static const sf::Time word_time = sf::seconds(4);
    sf::Clock last_press_clock;
    
    std::vector<bool> letter_bits;
    bool is_letter_said = false;
    bool is_word_said = true;

    class AllwaysFocusButton : public ui::BaseButton
    {
    public: 
        AllwaysFocusButton(Telegraph &parent);
        sf::Sound press_noise{res::morse_noise};
        sf::Clock clock_since_press;
        Telegraph &parent;

        void draw(unused sf::RenderTarget& target, unused sf::RenderStates states) const override {}
        sf::FloatRect get_global_bounds() const override {return {};};

        void m_on_click(double delta_time) override;
        void m_on_release(double delta_time) override;

        bool press_conditions() override;
    } button;
};