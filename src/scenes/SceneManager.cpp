#include "SceneManager.hpp"

SceneManager::sc_shptr SceneManager::get_current()
{
    return scenes.front();
}

void SceneManager::Scene::quit()
{
    scenes.pop(); 
    if(scenes.empty())
        throw std::runtime_error("no more scenes for executing");
}
