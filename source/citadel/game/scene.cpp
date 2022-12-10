//
//  scene.cpp
//  CitadelEngine
//
//  Created by Stephanie Barrett on 2022-12-09.
//  Copyright © 2022 Floating Citadel Games. All rights reserved.
//

#include "scene.h"

namespace citadel
{
    EntityID Scene::CreateEntity()
    {
        if (!freeEntities.empty())
        {
            EntityIndex newIndex = freeEntities.back();
            freeEntities.pop_back();
            EntityVersion newVersion = Entity::GetEntityVersion(entities[newIndex].id);
            EntityID newId = Entity::CreateEntityID(newIndex, newVersion);
            entities[newIndex].id = newId;
            return entities[newIndex].id;
        }

        entities.push_back({ entities.size(), ComponentMask() });
        return entities.back().id;
    }

    void Scene::DestroyEntity(EntityID id)
    {
        // set the id to -1 and add 1 to the version to invalidate any references to this entity
        EntityID newId = Entity::CreateEntityID(EntityIndex(-1), Entity::GetEntityVersion(id) + 1);
        EntityIndex entityIndex = Entity::GetEntityIndex(id);
        entities[entityIndex].id = newId;
        entities[entityIndex].mask.reset();
        freeEntities.push_back(entityIndex);
    }
    /*
    void Scene::Load(std::string path)
    {
        std::cout << "TODO!" << std::endl;
    }
    
    void Scene::AddGameObject(const std::shared_ptr<GameObject>&  gameObject)
    {
        std::lock_guard<std::mutex> guard(m_uninitializedGameObjectsMutex);
        m_uninitializedGameObjects.emplace_back(gameObject);
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
    

    void Scene::initializeGameObjects()
    {
        std::lock_guard<std::mutex> guard(m_uninitializedGameObjectsMutex);
        for (auto& gameObject : m_uninitializedGameObjects)
        {
            gameObject->onEnteredScene();
        }

        m_uninitializedGameObjects.clear();
    }

    void Scene::Tick(Time &deltaTime)
    {
        initializeGameObjects();

        for (auto& gameObject : m_gameObjects)
        {
            gameObject->Update(deltaTime);
        }

        for (auto& system : m_systems)
        {
            system->Update(deltaTime);
        }
    }

    void Scene::Draw() const
    {
        // std::cout << "TODO!" << std::endl;
        // Determine if base Scene should do anything
    }
    */
}