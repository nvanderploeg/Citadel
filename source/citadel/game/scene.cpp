#include "scene.h"

#include <iostream>

#include "system.h"
#include "gameObject.h"

namespace citadel
{

    void Scene::Load(std::string path)
    {
        std::cout << "TODO!" << std::endl;
    }

    
    void Scene::AddGameObject(const std::shared_ptr<GameObject>&  gameObject)
    {
        m_gameObjects.emplace_back(gameObject);
    }

    void Scene::RemoveGameObject(const std::shared_ptr<GameObject>&  gameObject)
    {
        auto it = m_gameObjects.begin();
        for (; it != m_gameObjects.end(); ++it) {
            if (gameObject == *it) { break; }
        }

        if (it == m_gameObjects.end()) {
            throw std::runtime_error("Couldn't find gameObject in scene to remove");
        }
        //Techincally slow on a vector, but meh!
        m_gameObjects.erase(it);
    }
    
    void Scene::AddSystem(const std::shared_ptr<System>& system)
    {
        m_systems.emplace_back(system);
    }
    
    void Scene::RemoveSystem(const std::shared_ptr<System>& system)
    {
        auto it = m_systems.begin();
        for (; it != m_systems.end(); ++it) {
            if (system == *it) { break; }
        }

        if (it == m_systems.end()) {
            throw std::runtime_error("Couldn't find system in scene to remove");
        }
        //Techincally slow on a vector, but meh!
        m_systems.erase(it);
    }
    

    void Scene::Tick(Time &deltaTime)
    {
        std::cout << "TODO!" << std::endl;
    }

    void Scene::Draw() const
    {
        std::cout << "TODO!" << std::endl;
    }

}