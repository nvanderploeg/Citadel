//
//  sceneStack.h
//  CitadelEngine
//
//  Created by Stephanie Barrett on 2022-12-19.
//  Copyright � 2022 Floating Citadel Games. All rights reserved.
//
#pragma once

#include "cTime.h"

namespace citadel
{
	class Scene;
	class InputRouter;

	class SceneStack
	{
	protected:
		std::shared_ptr<InputRouter> m_inputRouter;
		std::vector<std::unique_ptr<Scene>> m_scenes;

	public:
		SceneStack() = default;
		explicit SceneStack(const std::shared_ptr<InputRouter>& inputRouter);

		void Tick(const Time& deltaTime);
		void Draw();
		void Clear();
		void Push(std::unique_ptr<Scene> scene);
		void Pop();

		void SetInputRouter(const std::shared_ptr<InputRouter>& inputRouter);
	};

} // namespace citadel