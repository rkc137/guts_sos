#pragma once 

#include <SFML/Graphics.hpp>

#include <type_traits>
#include <queue>

#include "../core/DefaultWindowWrap.hpp"

template <typename WWT = DefaultWindowWrap>
class BaseSceneManager : public WWT
{
public:
    class Scene : public sf::Drawable, public WWT
    {
    public:
        /// @brief makes avery change per frame
        /// @param delta_time time is seconds after last frame
        virtual void update(double delta_time) = 0;
        /// @brief called when window change resolution
        virtual void resize() = 0;
        virtual ~Scene() = default;
    protected:
        /// @brief must be called to exit from current scene and step to the next
        void quit();
    };
    using sc_shptr = std::shared_ptr<Scene>;

    /// @brief add scene in queue of executing
    /// @tparam scene_t requires be delivered by Scene of manager 
    template <typename scene_t>
    static void add_scene() 
    requires std::is_base_of<Scene, scene_t>::value;
    
    /// @brief gets front scene of manager that currently (should be) running
    /// @return shared_ptr on current scene
    static sc_shptr get_current();
private:
    /// @brief queue that manage all scenes of manager
    inline static std::queue<sc_shptr> scenes;
};

/// @brief default scene manager
using SceneManager = BaseSceneManager<>;

#include "SceneManager.tpp"