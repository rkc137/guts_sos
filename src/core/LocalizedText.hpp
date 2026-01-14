#include <map>
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

    class String
    {
    public:
        using text_map = std::map<Lang, sf::String>;

        explicit String(text_map &&text) : texts(text) {}
        explicit operator sf::String()
        {
            return texts.at(current_language);
        }

    private:
        text_map texts;
    };

    static svector choose_vector(std::map<Lang, svector> &&map_strings) noexcept(false)
    {
        return map_strings.at(current_language);
    }
};

using LC = localization;