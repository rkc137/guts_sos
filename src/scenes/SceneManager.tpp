#include "SceneManager.hpp"

template <typename WWT>
BaseSceneManager<WWT>::sc_shptr BaseSceneManager<WWT>::get_current()
{
    // var exist only for executing validation of window once
    unused static bool init_win_check = [&](){
        WWT::check_window();
        return true;
    }();

    return current_scene;
}

template <typename WWT>
template <typename scene_t>
void BaseSceneManager<WWT>::start_scene()
requires std::is_base_of_v<Scene, scene_t>
{
    WWT::check_window();
    current_scene = std::make_shared<scene_t>();
    current_scene->resize();
}
