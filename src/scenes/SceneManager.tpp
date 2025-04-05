#include "SceneManager.hpp"

template <typename WWT>
BaseSceneManager<WWT>::sc_shptr BaseSceneManager<WWT>::get_current()
{
    return scenes.front();
}

template <typename WWT>
void BaseSceneManager<WWT>::Scene::quit()
{
    scenes.pop(); 
    if(scenes.empty())
        throw std::runtime_error("no more scenes for executing");
}
