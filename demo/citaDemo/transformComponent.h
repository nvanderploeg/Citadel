//
//  transformComponent.h
//  CitadelEngine Demo
//
//  Created by Stephanie Barrett on 2022-12-06.
//  Copyright � 2022 Floating Citadel Games. All rights reserved.
//
#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include <string>

struct TransformComponent
{
	virtual inline std::string type() const { return "transform"; }

	//Position in 3D space relative to parent
	glm::vec3 position = { 0, 0, 0 };

	//Scale
	glm::vec3 scale = { 1, 1, 1 };

	//Rotations
	glm::quat rotation = glm::identity<glm::quat>();
};
