//
//  entity.h
//  CitadelEngine
//
//  Created by Stephanie Barrett on 2022-12-09.
//  Copyright © 2022 Floating Citadel Games. All rights reserved.
//
#pragma once

#include <bitset>
#include <cstdint>

#include "component.h"

namespace citadel::ecs
{
#define INVALID_ENTITY CreateEntityId(EntityIndex(-1), 0)

    using EntityID = uint64_t;
    using EntityIndex = uint64_t;
    using EntityVersion = uint32_t;
    const ComponentID MAX_COMPONENT_TYPES = 64;
    using ComponentMask = std::bitset<MAX_COMPONENT_TYPES>;

    class Entity
    {
    public:
        EntityID id;
        ComponentMask mask;

        static inline EntityID CreateEntityID(EntityIndex index, EntityVersion version)
        {
            // Shift the index up 32, and put the version in the bottom
            return ((EntityID)index << 32) | ((EntityID)version);
        }

        static inline EntityIndex GetEntityIndex(EntityID id)
        {
            // Shift down 32 so we lose the version and get our index
            return id >> 32;
        }
        static inline EntityVersion GetEntityVersion(EntityID id)
        {
            // Cast to a 32 bit int to get our version number (loosing the top 32 bits)
            return (EntityVersion)id;
        }
        static inline bool IsEntityValid(EntityID id)
        {
            // Check if the index is our invalid index
            return (id >> 32) != EntityIndex(-1);
        }

    }; // class Entity
} // namespace citadel::ecs
