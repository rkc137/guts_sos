#include "StampLabel.hpp"

namespace ui
{

bool BaseStampLabel::is_done() const
{
    return stamp_iter == stamp_text.getSize();
}

BaseStampLabel::BaseStampLabel(Label &&label, sf::String text, sf::Time letter_time)
    : Label(label),
      stamp_text(text),
      letter_time(letter_time)
{
}

StampLabelSound::StampLabelSound(
    Label && label,
    sf::String text, 
    sf::Sound sound,
    sf::Time letter_time) 
    : BaseStampLabel(std::move(label), text, letter_time),
      sound(sound),
      sounds{sound, sound, sound}
{
}

void StampLabelSound::update(unused double delta_time)
{
    if(is_done() || clock.getElapsedTime() < letter_time)
        return;
    if(sounds_iter == sounds.size())
        sounds_iter = 0;
    sounds[sounds_iter].play();
    append_string(stamp_text[stamp_iter]);
    ++sounds_iter;
    ++stamp_iter;
    clock.restart();
}

StampLabelMusic::StampLabelMusic(
    Label &&label,
    sf::String text,
    sf::Music &music,
    sf::Time letter_time) 
    : BaseStampLabel(std::move(label), text, letter_time),
      voice(music)
{
}

StampLabelMusic::~StampLabelMusic()
{
    voice.pause();
}

void StampLabelMusic::update(unused double delta_time)
{
    if(is_done() && first_on_end)
    {
        first_on_end = false;
        voice.pause();
        return;
    }
    else if(is_done() || clock.getElapsedTime() < letter_time)
        return;
    else if(is_on_start)
    {
        is_on_start = false;
        voice.play();
    }
    append_string(stamp_text[stamp_iter]);
    ++stamp_iter;
    clock.restart();
}

}