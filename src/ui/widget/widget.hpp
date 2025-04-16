#pragma once 

#include <SFML/Graphics.hpp>

#include "../../core/WindowWrap.hpp"

namespace ui
{

template <typename WWT = DefaultWindowWrap>
class BaseWidget : public sf::Drawable, public sf::Transformable, public WWT
{
public:
    virtual ~BaseWidget() = default;
    virtual void update(unused double delta_time) {};
    virtual sf::FloatRect get_global_bounds() const = 0;

    enum class OriginState
    {
        left_up = 0,
        left_down = 1,
        center = 4
    };
    
protected:
    OriginState origin_state = OriginState::center;
    bool is_in_focus = false;
};

}