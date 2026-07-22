#pragma once

#include <unordered_map>
#include <SFML/System/String.hpp>

class localization
{
public:
    localization() = delete;

    inline static enum class Lang
    {
        eng,
        rus
    } current_language = Lang::eng;

    using svector = std::vector<sf::String>;
    using text_map = std::unordered_map<Lang, sf::String>;
    using string_map = std::unordered_map<Lang, svector>;

    class String
    {
    public:

        explicit String(text_map &&text) : texts(text) {}
        explicit operator sf::String()
        {
            return texts.at(current_language);
        }

    private:
        text_map texts;
    };

    static sf::String choose_string(text_map &&map_strings) noexcept(false)
    {
        return map_strings.at(current_language);
    }

    static svector choose_vector(string_map &&map_strings) noexcept(false)
    {
        return map_strings.at(current_language);
    }
};

using LC = localization;