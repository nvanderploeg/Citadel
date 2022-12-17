//
//  componentPool.cpp
//  CitadelEngine
//
//  Created by Stephanie Barrett on 2022-12-09.
//  Copyright � 2022 Floating Citadel Games. All rights reserved.
//

#include "componentPool.h"

namespace citadel::ecs
{
	ComponentPool::ComponentPool(EntityIndex size)
	{
		m_size = size;
		m_pData = new char[size * MAX_ENTITIES];
	}

	ComponentPool::~ComponentPool()
	{
		delete[] m_pData;
	}
} // namespace citadel::ecs