//
//  sceneStack.cpp
//  CitadelEngine
//
//  Created by Stephanie Barrett on 2022-12-19.
//  Copyright © 2022 Floating Citadel Games. All rights reserved.
//

#include "scene.h"
#include "inputRouter.h"
#include "sceneStack.h"


namespace citadel
{
	SceneStack::SceneStack(const std::shared_ptr<InputRouter>& inputRouter)
		: m_inputRouter(inputRouter)
	{
		// empty
	}

	void SceneStack::Tick(const Time& deltaTime)
	{
		m_scenes.back()->Tick(deltaTime);
	}

	void SceneStack::Draw()
	{
		for (auto const& itr : m_scenes)
		{
			itr->Draw();
		}
	}

	void SceneStack::Clear()
	{
		m_scenes.clear();
	}

	void SceneStack::Push(std::unique_ptr<Scene> scene)
	{
		m_scenes.emplace_back(std::move(scene));
		m_scenes.back()->OnEnter(m_inputRouter);
	}

	void SceneStack::Pop()
	{
		m_scenes.back()->OnExit(m_inputRouter);
		m_scenes.pop_back();
	}

	void SceneStack::SetInputRouter(const std::shared_ptr<InputRouter>& inputRouter)
	{
		m_inputRouter = inputRouter;
	}

} // namespace citadel