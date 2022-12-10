//
//  scene.h
//  CitadelEngine
//
//  Created by on .
//  Copyright � 2022 Floating Citadel Games. All rights reserved.
//
#pragma once

#include <vector>
#include <memory>
#include <string>
#include <mutex>

#include "cTime.h"
#include "ecs/entity.h"
#include "ecs/component.h"
#include "ecs/componentPool.h"

namespace citadel 
{
    using namespace ecs;

    class Scene
    {
    protected:
        std::vector<Entity> entities;
        std::vector<EntityIndex> freeEntities;
        std::vector<ComponentPool> componentPools;

    public:
        EntityID CreateEntity();
        void DestroyEntity(EntityID id);

        template<typename T>
        inline void AddComponent(EntityID id)
        {
            EntityIndex entityIndex = Entity::GetEntityIndex(id);
            
            if (entities[entityIndex].id != id)
                return;
            
            ComponentID componentId = Component::GetID<T>();

            // not enought component pool
            if (componentPools.size() <= componentId)
            {
                componentPools.resize(componentId + 1, nullptr);
            }

            // new component, make a new pool
            if (componentPools[componentId] == nullptr)
            {
                componentPools[componentId] = new ComponentPool(sizeof(T));
            }

            // look up the component in the pool and initialize
            T* pComponent = new (componentPools[componentId]->get(id)) T();

            // update the entity component mask
            entities[entityIndex].mask.set(componentId);

            return pComponent;
        }

        template<typename T>
        inline T* GetComponent(EntityID id)
        {
            EntityIndex entityIndex = Entity::GetEntityIndex(id);

            if (entities[entityIndex].id != id)
                return;

            ComponentID componentId = Component::GetID<T>();

            if (!entities[entityIndex].mask.test(componentId))
                return nullptr;

            T* pComponent = static_cast<T*>(componentPools[componentId]->get(id));
            return pComponent;
        }

        template<typename T>
        inline bool HasComponent(EntityID id)
        {
            return GetComponent<T>(id) != nullptr;
        }

        template<typename T>
        inline void RemoveComponent(EntityID id)
        {
            EntityIndex entityIndex = Entity::GetEntityIndex(id);

            if (entities[entityIndex].id != id)
                return;

            ComponentID componentId = Component::GetID<T>();
            entities[entityIndex].mask.reset(componentId);
        }
    };
/*
    class GameObject;
    class System;

    class Scene
    {
    protected:
        std::vector<std::shared_ptr<GameObject>> m_gameObjects;
        std::vector<std::shared_ptr<GameObject>> m_uninitializedGameObjects;
        std::vector<std::shared_ptr<System>> m_systems;
        std::mutex m_uninitializedGameObjectsMutex;

    public:
        Scene() = default;
        virtual ~Scene() = default;

        void Load(std::string path);

        void AddGameObject(const std::shared_ptr<GameObject>& gameObject);
        void RemoveGameObject(const std::shared_ptr<GameObject>& gameObject);
        void AddSystem(const std::shared_ptr<System>& system);
        void RemoveSystem(const std::shared_ptr<System>& system);

        void initializeGameObjects();

        virtual void Tick(Time &deltaTime);
        virtual void Draw() const;
    };
*/
}