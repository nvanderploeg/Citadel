//
//  sceneStack.h
//  CitadelEngine
//
//  Created by Stephanie Barrett on 2022-12-19.
//  Copyright � 2022 Floating Citadel Games. All rights reserved.
//
#pragma once
#include <memory>

#include "cTime.h"

namespace citadel
{
	class Scene;

	class SceneStack
	{
	protected:
		std::vector<std::unique_ptr<Scene>> m_scenes;

	public:
		void Tick(const Time& deltaTime);
		void Draw();
		void Clear();
		void Push(std::unique_ptr<Scene> scene);
		void Pop();
	};

} // namespace citadel