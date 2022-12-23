//
//  scene.cpp
//  CitadelEngine
//
//  Created by Stephanie Barrett on 2022-12-09.
//  Copyright © 2022 Floating Citadel Games. All rights reserved.
//

#include "registry.h"

namespace citadel::ecs
{

    EntityID Registry::CreateEntity()
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

        EntityID newId = Entity::CreateEntityID(entities.size(), 0);
        entities.push_back({ newId, ComponentMask() });
        return entities.back().id;
    }

    void Registry::DestroyEntity(EntityID id)
    {
        // set the id to -1 and add 1 to the version to invalidate any references to this entity
        EntityID newId = Entity::CreateEntityID(EntityIndex(-1), Entity::GetEntityVersion(id) + 1);
        EntityIndex entityIndex = Entity::GetEntityIndex(id);
        entities[entityIndex].id = newId;
        entities[entityIndex].mask.reset();
        freeEntities.push_back(entityIndex);
    }

    void Registry::Clear()
    {
        componentPools.clear();
        entities.clear();
        freeEntities.clear();
    }

} // namespace citadel::ecs