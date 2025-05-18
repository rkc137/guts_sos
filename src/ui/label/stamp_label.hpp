#pragma once

#include "label.hpp"

namespace ui
{

class StampLabel : public Label
{
public:
    explicit StampLabel(
        Label&& label,
        sf::String text,
        sf::Sound sound,
        sf::Time letter_time = sf::seconds(0.2)
    );
    void update(double delta_time) override;
    bool is_done() const;
private:
    sf::Clock clock;
    sf::String stamp_text;
    sf::Sound sound;
    sf::Time letter_time;
    std::array<sf::Sound, 3> sounds;
    std::size_t stamp_iter = 0;
    std::size_t sounds_iter = 0;
};

}