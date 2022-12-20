//
//  scene.cpp
//  CitadelEngine
//
//  Created by Stephanie Barrett on 2022-12-11.
//  Copyright � 2022 Floating Citadel Games. All rights reserved.
//

#include "scene.h"
#include "sceneStack.h"
#include <citadel/graphics/graphics.h>

namespace citadel
{
	Scene::Scene(const std::shared_ptr<SceneStack>& sceneStack)
		: m_sceneStack(sceneStack)
	{
		m_registry = std::make_shared<ecs::Registry>();
	}

	void Scene::OnEnter(const std::shared_ptr<InputRouter>& inputRouter)
	{
		BindInput(inputRouter);

		//TODO: this should go wherever the Camera class ends up
		VulkanGraphics::Instance()->SetFoV(90.f);

	}

	void Scene::OnExit(const std::shared_ptr<InputRouter>& inputRouter)
	{
		FreeInput(inputRouter);
		m_registry->Clear();
	}
}