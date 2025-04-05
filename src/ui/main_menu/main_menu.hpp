#pragma once

#include <SFML/Graphics.hpp>

#include <functional>
#include <string>

#include "../../res/res.hpp"

#include "../label/label.hpp"
#include "../buttons/label_button.hpp"

namespace ui
{

class Main_menu : public sf::Drawable
{
public:
    Main_menu(sf::RenderWindow &window);
    void update(double delta_time);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    Label_button start;
    Label_button settings;
    Label_button exit;
private:
    const sf::RenderWindow &window;
    Label logo;
};

}