//
//  scene.h
//  CitadelEngine
//
//  Created by Stephanie Barrett on 2022-12-11.
//  Copyright � 2022 Floating Citadel Games. All rights reserved.
//
#pragma once

#include "tickable.h"
#include "ecs/registry.h"

#include "cTime.h"
#include "renderer.h"

namespace citadel 
{
    class InputRouter;

    class Scene : public ITickable
    {
    protected:
        std::shared_ptr<ecs::Registry> m_registry;
        std::shared_ptr<Renderer> m_renderer;
    public:
        Scene() { m_registry = std::make_shared<ecs::Registry>(); }
        virtual void Tick(const Time& deltaTime) = 0;
        virtual void Draw() = 0;

        virtual void BindInput(const std::shared_ptr<InputRouter>& inputRouter) = 0;
        virtual void FreeInput(const std::shared_ptr<InputRouter>& inputRouter) = 0;
    };

} // namespace citadel