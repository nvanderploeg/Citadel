//
//  registry.h
//  CitadelEngine
//
//  Created by Stephanie Barrett on 2022-12-11.
//  Copyright © 2022 Floating Citadel Games. All rights reserved.
//
#pragma once

#include <vector>
#include <memory>
#include <string>
#include <mutex>

#include "entity.h"
#include "componentPool.h"
#include "filter.h"

namespace citadel 
{
    namespace ecs
    {
        class Registry
        {
        private:
            friend class Filter<>;

            std::vector<Entity> entities;
            std::vector<EntityIndex> freeEntities;
            std::vector<ComponentPool*> componentPools;

        public:
            EntityID CreateEntity();
            void DestroyEntity(EntityID id);

            template<typename T>
            inline T* AddComponent(EntityID id)
            {
                EntityIndex entityIndex = Entity::GetEntityIndex(id);

                if (entities[entityIndex].id != id)
                    return nullptr;

                ComponentID componentId = Component::GetID<T>();

                // not enough component pool
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
                    return nullptr;

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

        }; // class Registry
    } // namespace ecs
} // namespace citadel