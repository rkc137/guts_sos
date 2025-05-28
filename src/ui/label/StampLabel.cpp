#include "StampLabel.hpp"

namespace ui
{

void BaseStampLabel::reset_text(sf::String str)
{
    clear();
    reset_sound();
    done = false;
    stamp_text = str;
    stamp_iter = 0;
}

bool BaseStampLabel::is_done() const
{
    return done;
}

sf::Time BaseStampLabel::last_stamp() const
{
    return clock.getElapsedTime();
}

BaseStampLabel::BaseStampLabel(Label &&label, sf::String text, sf::Time letter_time)
    : Label(label),
      stamp_text(text),
      letter_time(letter_time)
{
}

void BaseStampLabel::calc_is_done()
{
    done = stamp_iter == stamp_text.getSize();
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

void StampLabelSound::reset_sound()
{
    for(auto &s : sounds)
        s.stop();
    sounds_iter = 0;
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
    calc_is_done();
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

void StampLabelMusic::reset_sound()
{
    is_on_start = true;
    first_on_end = true;
}

void StampLabelMusic::update(unused double delta_time)
{
    if(!is_done())
    {
        if(is_on_start)
        {
            is_on_start = false;
            voice.play();
        }
        else if(clock.getElapsedTime() < letter_time)
            return;
        append_string(stamp_text[stamp_iter]);
        ++stamp_iter;
        clock.restart();
        calc_is_done();
    }
    else if(first_on_end)
    {
        first_on_end = false;
        voice.stop();
    }
}

}