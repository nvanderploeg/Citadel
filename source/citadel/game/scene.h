//
//  scene.h
//  CitadelEngine
//
//  Created by Stephanie Barrett on 2022-12-11.
//  Copyright © 2022 Floating Citadel Games. All rights reserved.
//
#pragma once

#include "tickable.h"
#include "ecs/registry.h"

namespace citadel
{

    class Scene : public ITickable
    {
    protected:
        ecs::Registry registry;

    public:
        virtual void Tick(const Time& deltaTime) = 0;
        virtual void Draw() = 0;
    };

} // namespace citadel