#include "res.hpp"

#include "battery/embed.hpp"

#include "../core/logger/Logger.hpp"

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
        {blocknote_morse,   "blocknote/blocknote_alphabet_mini.png"},
        {blocknote_onside,  "blocknote/blocknote_blank_onside.png"},
        {troop,             "faces/troop.png"},
        {commander,         "faces/commander.png"},
        {light,             "bunker/light.png"},
        {bunker,            "bunker/bunker.png"},
        {splash,            "splash/splash.png"}
    });
    const auto sounds_load_list = std::to_array<Setup<sf::SoundBuffer>>({
        {morse_noise,       "morse.wav"},
        {stamp,             "stamp.wav"},
        {print,             "blocknote/print.wav"},
        {incoming,          "explosion/incoming.wav"}
    });
    const auto music_load_list = std::to_array<Setup<sf::Music>>({
        {distance_explosions,   "explosion/distance_explosions.wav"},
        {carterattack,          "explosion/carterattack.wav"},
        {distance_battle,       "explosion/distance_battle.wav"},
        {voice,                 "faces/voice.wav"},
        {march,                 "march.wav"}
    });
    const auto fonts_load_list = std::to_array<Setup<sf::Font>>({
        {default_font,   "fonts/dejavu-sans/DejaVuSans.ttf"},
        {cybersomething, "fonts/Cybersomething.ttf"},
        {comicsansMSrus, "fonts/comic-sans-ms-pixel-rus-eng-legacy.otf"},
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

    std::unordered_map<Lang, std::string> lang_json = {
        {Lang::eng, b::embed<"translations/eng.json">() },
        {Lang::rus, b::embed<"translations/rus.json">() }
    };
    text = json::parse(lang_json[current_language], nullptr, true, true);

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

sf::Font& res::get_hand_font()
{
    switch(current_language)
    {
    case Lang::eng:
        return too_much_ink;
    case Lang::rus:
        return comicsansMSrus;
    default:
        return default_font;
    }
}

res::TextHolder res::get_scene_text(std::string_view scene_index)
{
    TextHolder ret;
    const auto block = std::make_shared<json>(text[scene_index]);
    ret.proxy_string.block = block;
    ret.proxy_text.block = block;
    return ret;
}

sf::String res::TextHolder::ProxyStrings::operator[](std::string_view label) const
{
    try {
        auto s = block->at(label).get<std::string>();
        return sf::String::fromUtf8(s.begin(), s.end());
    } catch (const nlohmann::json::exception& e) {
        dbg() << e.what() << label << block;
        return "BAD JSON STRING";
    }
}

std::vector<sf::String> res::TextHolder::ProxyTexts::operator[](std::string_view label) const
{
    try {
        std::vector<sf::String> ret;
        auto b = block->at(label).get<std::vector<std::string>>();
        for(auto s : b)
            ret.emplace_back(sf::String::fromUtf8(s.begin(), s.end()));
        return ret;
    } catch (const nlohmann::json::exception& e) {
        dbg() << e.what();
        return {"BAD JSON", "BAD JSON", "BAD JSON"};
    }
}
