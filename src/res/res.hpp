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
    inlstc bool loaded = false;

public:
    res() = delete;
    static void load();

    using fspath = std::filesystem::path;
#ifndef NDEBUG
    inlstc const fspath res_path = "../res/";
#elif
    inlstc const fspath res_path = "./res/";
#endif

    //resolution that was used while making assets
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
    
    inlstc sf::Texture 
        default_texture, blocknote_blank, blocknote_morse, blocknote_onside,
        answer_pepper, splash, bunker, troop, commander, light;
    inlstc sf::Font default_font, cybersomething, too_much_ink;
    inlstc sf::SoundBuffer morse_noise, stamp, print, incoming;
    inlstc sf::Music distance_explosions, distance_battle, carterattack, voice;
    
    inlstc const sf::String app_name = "guts:s.o.s";
    inlstc bool is_loaded() { return loaded; }
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