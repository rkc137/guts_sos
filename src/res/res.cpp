#include "res.hpp"

void res::load()
{
    // Setup types
    using SoundSetup = std::pair<sf::SoundBuffer&, fspath>;
    using MusicSetup = std::pair<sf::Music&, fspath>;
    using FontSetup = std::pair<sf::Font&, fspath>;
    struct TextureSetup
    {
        Texture &texture;
        fspath path;
        TextureSetup(Texture &texture, fspath &&path, TextureMetaInfo &&info)
            : texture(texture), path(path)
        {
            static_cast<TextureMetaInfo&>(texture) = std::move(info);
        }
    };

    // Resources declaration
    const auto texture_load_list = std::to_array<TextureSetup>({
        {default_texture,   "place_holder.png",            {{64, 64},   {1}}},
        {blocknote_blank,   "blocknote/blocknote_blank.png",    {{514, 600}, {1}}},
        {blocknote_morse,   "blocknote/blocknote_alphabet.png", {{514, 600}, {1}}},
        {blocknote_onside,  "blocknote/blocknote_blank_onside.png", {{600, 257}, {1}}},
        {troop,             "faces/troop.png",             {{512, 512}, {1}}},
        {commander,         "faces/commander.png",         {{512, 512}, {1}}},
        {light,             "bunker/light.png",            {{1920*2, 1080*2},   {1}}},
        {bunker,            "bunker/bunker.png",           {{1920, 1080},   {1}}},
        {splash,            "splash/splash.png",           {{128, 128}, {1}}}
    });
    const auto sounds_load_list = std::to_array<SoundSetup>({
        {morse_noise, "morse.wav"},
        {stamp, "stamp.wav"},
        {incoming, "explosion/incoming.wav"}
    });
    const auto music_load_list = std::to_array<MusicSetup>({
        {distance_explosions, "explosion/distance_explosions.wav"},
        {carterattack, "explosion/carterattack.wav"},
        {distance_battle, "explosion/distance_battle.wav"},
        {voice, "faces/voice.wav"}
    });
    const auto fonts_load_list = std::to_array<FontSetup>({
        {default_font,   "fonts/CENTURY.TTF"},
        {cybersomething, "fonts/Cybersomething.ttf"},
        {too_much_ink,   "fonts/TooMuchInk.ttf"}
    });

    // Loading
    for(auto &setup : texture_load_list)
    {
        auto &txr = setup.texture;
        if(!txr.loadFromFile(res_path / setup.path))
        {
            if(&txr == &default_texture)
                throw std::runtime_error("even default texture was not loaded");

            txr = default_texture;
            continue;
        }
        
        txr.setSmooth(is_smooth);
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
