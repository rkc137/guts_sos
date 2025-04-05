#pragma once 

#include <SFML/Graphics.hpp>

#include <queue>

#include "../core/DefaultWindowWrap.hpp"

template <typename WWT>
class BaseSceneManager : public WWT
{
public:
    class Scene : public sf::Drawable, public WWT
    {
    public:
        /// @brief makes avery change per frame
        /// @param delta_time time is seconds after last frame
        virtual void update(double delta_time) = 0;
        virtual ~Scene() = default;
    protected:
        void quit();
    };
    using sc_shptr = std::shared_ptr<Scene>;

    template <typename scene_t>
    static void add_scene(sf::RenderWindow &window)
    {
        sc_shptr scene(new scene_t(window));
        scenes.push(scene);
    }
    
    static sc_shptr get_current();
private:
    // static sf::RenderWindow *window;
    inline static std::queue<sc_shptr> scenes;//TODO: its must be not queue
};

using SceneManager = BaseSceneManager<DefaultWindowWrap>;

#include "SceneManager.tpp"