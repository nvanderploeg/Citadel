//
//  scene.cpp
//  CitadelEngine
//
//  Created by Stephanie Barrett on 2022-12-11.
//  Copyright © 2022 Floating Citadel Games. All rights reserved.
//

#include "scene.h"
#include "sceneStack.h"

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
	}

	void Scene::OnExit(const std::shared_ptr<InputRouter>& inputRouter)
	{
		FreeInput(inputRouter);
		m_registry->Clear();
	}
}