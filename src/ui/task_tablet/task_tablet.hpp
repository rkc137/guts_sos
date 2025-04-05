#pragma once 

#include "../widget/widget.hpp"
#include "../label/label.hpp"
#include "../buttons/label_button.hpp"
#include "../../res/res.hpp"

namespace ui
{

class Task_tablet : public Widget
{
public:
    Task_tablet(const sf::RenderWindow &window);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
    void m_on_touch(double delta_time) override;
    void m_on_afk(double delta_time) override;
    sf::FloatRect get_global_bounds() const override;

private:
    sf::Sprite sprite {res::task_tablet};
    mutable std::vector<Label> tasks;
    Label_button button;
};


}
