#include "res.hpp"

template <typename T>
struct Setup 
{
    T& reference;
    res::fspath path;
};

void res::load()
{
    const auto texture_load_list = std::to_array<Setup<sf::Texture>>({
        {default_texture,   "place_holder.png"},
        {answer_pepper,     "blocknote/answer_pepper.png"},
        {blocknote_blank,   "blocknote/blocknote_blank.png"},
        {blocknote_morse,   "blocknote/blocknote_alphabet.png"},
        {blocknote_onside,  "blocknote/blocknote_blank_onside.png"},
        {troop,             "faces/troop.png"},
        {commander,         "faces/commander.png"},
        {light,             "bunker/light.png"},
        {bunker,            "bunker/bunker.png"},
        {splash,            "splash/splash.png"}
    });
    const auto sounds_load_list = std::to_array<Setup<sf::SoundBuffer>>({
        {morse_noise, "morse.wav"},
        {stamp, "stamp.wav"},
        {print, "blocknote/print.wav"},
        {incoming, "explosion/incoming.wav"}
    });
    const auto music_load_list = std::to_array<Setup<sf::Music>>({
        {distance_explosions, "explosion/distance_explosions.wav"},
        {carterattack, "explosion/carterattack.wav"},
        {distance_battle, "explosion/distance_battle.wav"},
        {voice, "faces/voice.wav"}
    });
    const auto fonts_load_list = std::to_array<Setup<sf::Font>>({
        {default_font,   "fonts/dejavu-sans/DejaVuSans.ttf"},
        {cybersomething, "fonts/Cybersomething.ttf"},
        {too_much_ink,   "fonts/TooMuchInk.ttf"}
    });

    for(auto &[texture, path] : texture_load_list)
    {
        if(!texture.loadFromFile(res_path / path))
            texture = default_texture;
        texture.setSmooth(is_smooth);
    }
    for(auto &[font, path] : fonts_load_list)
        if(!font.openFromFile(res_path / path))
            font = default_font;
    for(auto &[sound, path] : sounds_load_list)
        if(!sound.loadFromFile(res_path / path))
            throw std::runtime_error("bruh wha");
    for(auto &[music, path] : music_load_list)
        if(!music.openFromFile(res_path / path))
            throw std::runtime_error("bruh wha");
    loaded = true;
}

sf::Vector2f res::get_scale(sf::Vector2f wsize)
{
    auto scale = std::max(
        std::abs(wsize.x / res::target_video_mode.x),
        std::abs(wsize.y / res::target_video_mode.y)
    );
    return {scale, scale};
}
