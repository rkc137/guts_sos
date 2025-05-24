#include "res.hpp"

res::TextureSetup::TextureSetup(Texture &texture, fspath &&path, TextureMetaInfo &&info)
    : texture(texture), path(path)
{
    static_cast<TextureMetaInfo&>(texture) = std::move(info);
}

void res::load()
{
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
        
        txr.setSmooth(false);
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
