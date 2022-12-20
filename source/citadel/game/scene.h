//
//  scene.h
//  CitadelEngine
//
//  Created by Stephanie Barrett on 2022-12-11.
//  Copyright � 2022 Floating Citadel Games. All rights reserved.
//
#pragma once

#include "cTime.h"
#include "renderer.h"
#include "ecs/registry.h"

namespace citadel 
{
    class InputRouter;
    class SceneStack;

    class Scene
    {
    protected:
        std::shared_ptr<ecs::Registry> m_registry;
        std::shared_ptr<Renderer> m_renderer;
        std::shared_ptr<SceneStack> m_sceneStack;

    public:
        Scene(const std::shared_ptr<SceneStack>& sceneStack);
        virtual void Tick(const Time& deltaTime) = 0;
        virtual void Draw() = 0;

        virtual void BindInput(const std::shared_ptr<InputRouter>& inputRouter) = 0;
        virtual void FreeInput(const std::shared_ptr<InputRouter>& inputRouter) = 0;

        virtual void OnEnter(const std::shared_ptr<InputRouter>& inputRouter);
        virtual void OnExit(const std::shared_ptr<InputRouter>& inputRouter);
    };

} // namespace citadel