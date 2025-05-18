#include "stamp_label.hpp"

namespace ui
{

ui::StampLabel::StampLabel(
    Label &&label,
    sf::String text,
    sf::Sound sound,
    sf::Time letter_time) :
        Label(label),
        stamp_text(text),
        sound(sound),
        letter_time(letter_time),
        sounds({sound, sound, sound})
{
}

bool StampLabel::is_done() const
{
    return stamp_iter == stamp_text.getSize();
}

void StampLabel::update(unused double delta_time)
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

}