#pragma once 

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <filesystem>
#include <vector>
#include <array>
#include <map>

#define inlstc inline static

class res
{
private:
    using fspath = std::filesystem::path;
#ifndef NDEBUG
    inlstc const fspath res_path = "D:/projects/S.O.S/res/";
#elif
    inlstc const fspath res_path = "../res/";
#endif
    struct TextureMetaInfo
    {
        sf::Vector2i frame_size;
        std::vector<int> animations_lengths;
    };

public:

    res() = delete;
    static void load();

    //resolution that was used for assets
    inlstc constexpr sf::Vector2f target_video_mode{1280, 720};
    inlstc constexpr bool is_smooth = true;
    static sf::Vector2f get_scale(sf::Vector2f wsize);
    template <typename T>
    requires (std::is_arithmetic_v<T>)
    static sf::Vector2f get_adaptive_scale(
        sf::Vector2<T> wsize,
        sf::Vector2<T> texture_size,
        sf::Vector2f ratio = {1.f, 1.f}
    );
    
    struct Texture : public sf::Texture, public TextureMetaInfo {};
    inlstc Texture 
        default_texture, blocknote_blank, blocknote_morse, blocknote_onside,
        splash, bunker, troop, commander, light;
    inlstc sf::Font default_font, cybersomething, too_much_ink;
    inlstc sf::SoundBuffer morse_noise, stamp, incoming;
    inlstc sf::Music distance_explosions, distance_battle, carterattack, voice;
    
    inlstc const sf::String app_name = "guts:s.o.s";
    inlstc bool is_loaded() { return loaded; }

private:
    inlstc bool loaded = false;

    struct TextureSetup
    {
        TextureSetup(Texture &texture, fspath &&path, TextureMetaInfo &&info);
        Texture &texture;
        fspath path;
        TextureMetaInfo info;
    };

    inlstc const std::vector<TextureSetup> texture_load_list = {
        {default_texture,   "place_holder.png",            {{64, 64},   {1}}},
        {blocknote_blank,   "blocknote/blocknote_blank.png",    {{514, 600}, {1}}},
        {blocknote_morse,   "blocknote/blocknote_alphabet.png", {{514, 600}, {1}}},
        {blocknote_onside,   "blocknote/blocknote_blank_onside.png", {{600, 257}, {1}}},
        {troop,             "faces/troop.png",             {{512, 512}, {1}}},
        {commander,         "faces/commander.png",         {{512, 512}, {1}}},
        {light,             "bunker/light.png",            {{1920*2, 1080*2},   {1}}},
        {bunker,            "bunker/bunker.png",           {{1920, 1080},   {1}}},
        {splash,            "splash/splash.png",           {{128, 128}, {1}}}
    };

    inlstc const std::vector<std::pair<sf::SoundBuffer&, fspath>> sounds_load_list = {
        {morse_noise, "morse.wav"},
        {stamp, "stamp.wav"},
        {incoming, "explosion/incoming.wav"}
    };

    inlstc const std::vector<std::pair<sf::Music&, fspath>> music_load_list = {
        {distance_explosions, "explosion/distance_explosions.wav"},
        {carterattack, "explosion/carterattack.wav"},
        {distance_battle, "explosion/distance_battle.wav"},
        {voice, "faces/voice.wav"}
    };

    inlstc const std::vector<std::pair<sf::Font&, fspath>> fonts_load_list = {
        {default_font, "fonts/dejavu-sans/DejaVuSans.ttf"},
        {cybersomething, "fonts/Cybersomething.ttf"},
        {too_much_ink, "fonts/TooMuchInk.ttf"}
    };

public:
    inlstc const std::array<sf::String, 3> intro_texts = {
        L"we were driven into a corner",
        L"the secret telegraph wire is all that remains",
        L"they will be here soon..."
    };
    
    //true is -
    inlstc const std::map<std::vector<bool>, char> morse_codes = {
        {{0, 1},        'A'},
        {{1, 0, 0, 0},  'B'},
        {{1, 0, 1, 0},  'C'},
        {{1, 0, 0},     'D'},
        {{0},           'E'},
        {{0, 0, 1, 0},  'F'},
        {{1, 1, 0},     'G'},
        {{0, 0, 0, 0},  'H'},
        {{0, 0},        'I'},
        {{0, 1, 1, 1},  'J'},
        {{1, 0, 1},     'K'},
        {{0, 1, 0, 0},  'L'},
        {{1, 1},        'M'},
        {{1, 0},        'N'},
        {{1, 1, 1},     'O'},
        {{0, 1, 1, 0},  'P'},
        {{1, 1, 0, 1},  'Q'},
        {{0, 1, 0},     'R'},
        {{0, 0, 0},     'S'},
        {{1},           'T'},
        {{0, 0, 1},     'U'},
        {{0, 0, 0, 1},  'V'},
        {{0, 1, 1},     'W'},
        {{1, 0, 0, 1},  'X'},
        {{1, 0, 1, 1},  'Y'},
        {{1, 1, 0, 0},  'Z'},
        {{1, 1, 1, 1, 1}, '0'},    // -----
        {{0, 1, 1, 1, 1}, '1'},    // .----
        {{0, 0, 1, 1, 1}, '2'},    // ..---
        {{0, 0, 0, 1, 1}, '3'},    // ...--
        {{0, 0, 0, 0, 1}, '4'},    // ....-
        {{0, 0, 0, 0, 0}, '5'},    // .....
        {{1, 0, 0, 0, 0}, '6'},    // -....
        {{1, 1, 0, 0, 0}, '7'},    // --...
        {{1, 1, 1, 0, 0}, '8'},    // ---..
        {{1, 1, 1, 1, 0}, '9'},
        {{0, 0, 0, 0, 0, 0, 0, 0}, '\b'}
    };
};

template <typename T>
requires (std::is_arithmetic_v<T>)
sf::Vector2f res::get_adaptive_scale(
        sf::Vector2<T> wsize,
        sf::Vector2<T> texture_size,
        sf::Vector2f ratio)
{
    auto winsize = static_cast<sf::Vector2f>(wsize);
    auto textrsize = static_cast<sf::Vector2f>(texture_size);

    auto base_scale = get_scale(winsize);
    auto scaled_size = sf::Vector2f(textrsize.x * base_scale.x, textrsize.y * base_scale.y);
    auto max_size = sf::Vector2f(winsize.x * ratio.x, winsize.y * ratio.y);
    
    sf::Vector2f scale = base_scale;
    if(scaled_size.x > max_size.x)
        scale.x = max_size.x / textrsize.x;
    if(scaled_size.y > max_size.y)
        scale.y = max_size.y / textrsize.y;
    
    auto final_scale = std::min(scale.x, scale.y);
    return {final_scale, final_scale};
}

#undef inlstc