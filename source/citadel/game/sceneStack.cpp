//
//  sceneStack.cpp
//  CitadelEngine
//
//  Created by Stephanie Barrett on 2022-12-19.
//  Copyright � 2022 Floating Citadel Games. All rights reserved.
//

#include "sceneStack.h"
#include "scene.h"

namespace citadel
{
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
		m_scenes.back()->OnEnter();
	}

	void SceneStack::Pop()
	{
		m_scenes.back()->OnExit();
		m_scenes.pop_back();
	}
} // namespace citadel