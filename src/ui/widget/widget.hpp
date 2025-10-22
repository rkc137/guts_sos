#pragma once 

#include <SFML/Graphics.hpp>

#include "../../core/WindowWrap.hpp"

namespace ui
{

enum class OriginState
{
    left_up = 0,
    left_down = 1,
    right_up = 2,
    right_down = 3,
    center = 4
};

template <typename WWT = DefaultWindowWrap>
class BaseWidget : public sf::Drawable, public sf::Transformable, public WWT
{
public:
    virtual ~BaseWidget() = default;
    virtual sf::FloatRect get_global_bounds() const = 0;  
    virtual void update(unused double delta_time) {};
    [[nodiscard]] virtual OriginState get_origin_state() const { return origin_state; }
    virtual void set_origin_state(OriginState state) { origin_state = state; }

protected:
    OriginState origin_state = OriginState::center;
    bool is_in_focus = false;
};

}