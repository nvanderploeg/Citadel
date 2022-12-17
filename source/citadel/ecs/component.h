//
//  component.h
//  CitadelEngine
//
//  Created by Stephanie Barrett on 2022-12-09.
//  Copyright � 2022 Floating Citadel Games. All rights reserved.
//
#pragma once

#include <cstdint>

namespace citadel::ecs
{
    using ComponentID = uint64_t;

    namespace Component
    {

        extern ComponentID s_componentTypeCounter;

        // Each time this is called on a new component type you�ll get a new unique ID, because static magic.
        template <class T>
        ComponentID GetID()
        {
            static ComponentID s_componentTypeId = s_componentTypeCounter++;
            return s_componentTypeId;
        }

    } // namespace Component
} // namespace citadel::ecs

