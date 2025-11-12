#pragma once

#include <array>

#include "SceneManager.hpp"
#include "local_scenes/Curtain.hpp"
#include "../ui/label/StampLabel.hpp"
#include "levels/Level1.hpp"

class Intro : public SceneManager::Scene
{
public:
    Intro();
    ~Intro() = default;
    void update(double delta_time) override;
    void resize() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    const std::vector<sf::String> intro_texts = LC::choose_vector({{
        LC::Lang::eng, {
            L"we were driven into a corner",
            L"the secret telegraph wire is all that remains",
            L"they will be here soon..."
        }
    }});
    const sf::Time pause = sf::seconds(1.3f);
    const sf::Time disappear_duration = sf::seconds(4);
    Curtain curtain{false, Curtain::ShowTypes::only_disappearnce, pause, pause, disappear_duration};
    sf::Clock clock;
    int volume = 100;
    bool text_done_check = false;
    bool done_check = false;
    std::vector<ui::StampLabelSound> texts;
    std::size_t active_text_iter = 0;
};