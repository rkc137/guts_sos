#include "SceneManager.hpp"

template <typename WWT>
BaseSceneManager<WWT>::sc_shptr BaseSceneManager<WWT>::get_current()
{
    if(scenes.empty())
        throw std::runtime_error("no more scenes for executing");
    return scenes.front();
}

template <typename WWT>
void BaseSceneManager<WWT>::Scene::quit()
{
    scenes.pop();
}

template <typename WWT>
template <typename scene_t>//, typename scene_t>
void BaseSceneManager<WWT>::add_scene()
requires std::is_base_of<Scene, scene_t>::value
{
    sc_shptr scene(new scene_t);
    scene->resize();
    scenes.push(scene);
}
