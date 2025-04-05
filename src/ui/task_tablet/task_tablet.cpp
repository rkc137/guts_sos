#include "task_tablet.hpp"

namespace ui
{

Task_tablet::Task_tablet(const sf::RenderWindow &window) 
    : Widget(window), button(Label(window, "spodaspodapsodpasodpaosdpo"))
{
    sprite.setOrigin({sprite.getTextureRect().width / 2.f, 0});

    // tasks[0].text.setStyle(sf::Text::StrikeThrough);
    sprite.setScale({2, 2});
    for(int i = 0; i < 5; i++)
    {
        tasks.emplace_back(window, "task " + std::to_string(i + 1));

        sf::FloatRect tRect = tasks[i].text.getLocalBounds();
        //     text.setOrigin(textRect.left + textRect.width / 2.0f,
        //    textRect.top  + textRect.height / 2.0f);
        tasks[i].setPosition({0, tasks[0].text.getCharacterSize() * float(i) + 60});
    }
}

void Task_tablet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite, states);
    for(auto &t : tasks)
        target.draw(t, states);
}

void Task_tablet::m_on_touch(double delta_time)
{
    relative_position += {0 , -15.f * float(delta_time)};
}
void Task_tablet::m_on_afk(double delta_time) 
{
    // relative_position += {0 , 15.0 * delta_time};
}

sf::FloatRect Task_tablet::get_global_bounds() const
{
    return sprite.getGlobalBounds();
}

}