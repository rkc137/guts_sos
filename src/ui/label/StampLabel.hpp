#pragma once

#include "label.hpp"

namespace ui
{

class BaseStampLabel : public Label
{
public:
    void reset_text(sf::String str);
    void update(double delta_time) override = 0;
    bool is_done() const;
    sf::Time last_stamp() const;
protected:
    BaseStampLabel(
        Label&& label,
        sf::String text,
        sf::Time letter_time
    );
    void calc_is_done();
    bool done = false;
    sf::String stamp_text;
    std::size_t stamp_iter = 0;
    sf::Time letter_time;
    sf::Clock clock;
};

class StampLabelSound : public BaseStampLabel
{
public:
    explicit StampLabelSound(
        Label&& label,
        sf::String text,
        sf::Sound sound,
        sf::Time letter_time = sf::seconds(0.2)
    );
    void update(double delta_time) override;
private:
    sf::Sound sound;
    std::array<sf::Sound, 3> sounds;
    std::size_t sounds_iter = 0;
};

class StampLabelMusic : public BaseStampLabel
{
public:
    explicit StampLabelMusic(
        Label&& label,
        sf::String text,
        sf::Music &voice,
        sf::Time letter_time = sf::seconds(0.2)
    );
    ~StampLabelMusic();
    void update(double delta_time) override;
private:
    bool is_on_start = true;
    bool first_on_end = true;
    sf::Music &voice;
};

}