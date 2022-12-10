//
//  transformComponent.h
//  CitadelEngine
//
//  Created by Stephanie Barrett on 2022-12-06.
//  Copyright � 2022 Floating Citadel Games. All rights reserved.
//

#ifndef __TRANSFORM_COMPONENT_H__
#define __TRANSFORM_COMPONENT_H__

#include "component.h"

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include <string>

//namespace citadel
//{

	struct TransformComponent// : public Component
	{
		virtual inline std::string getType() const { return "transform"; }

		//Position in 3D space relative to parent
		glm::vec3 position = { 0, 0, 0 };

		//Rotations
		glm::quat rotation = glm::identity<glm::quat>();

		//Scale
		glm::vec3 scale = { 1, 1, 1 };

	};

//} // namespace citadel

#endif // __TRANSFORM_COMPONENT_H__