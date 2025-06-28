#include "SceneManager.hpp"

template <typename WWT>
BaseSceneManager<WWT>::sc_shptr BaseSceneManager<WWT>::get_current()
{
    // var exist only for executing validation of window once 
    unused static bool init_win_check = [&](){ 
        WWT::check_window();
        return true;
    }();

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
template <typename scene_t>
void BaseSceneManager<WWT>::add_scene() 
requires std::is_base_of_v<Scene, scene_t>
{
    WWT::check_window();
    sc_shptr scene(new scene_t);
    scene->resize();
    scenes.push(scene);
}
