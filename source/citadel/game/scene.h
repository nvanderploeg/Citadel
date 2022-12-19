//
//  scene.h
//  CitadelEngine
//
//  Created by Stephanie Barrett on 2022-12-11.
//  Copyright � 2022 Floating Citadel Games. All rights reserved.
//
#pragma once

#include "cTime.h"
#include "ecs/registry.h"

namespace citadel 
{
    class InputRouter;

    class Scene
    {
    protected:
        std::shared_ptr<ecs::Registry> m_registry;

    public:
        Scene() { m_registry = std::make_shared<ecs::Registry>(); }
        virtual void Tick(const Time& deltaTime) = 0;
        virtual void Draw() = 0;

        virtual void BindInput(const std::shared_ptr<InputRouter>& inputRouter) = 0;
        virtual void FreeInput(const std::shared_ptr<InputRouter>& inputRouter) = 0;

        virtual void OnEnter() = 0;
        virtual void OnExit() = 0;
    };

} // namespace citadel