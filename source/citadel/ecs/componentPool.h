//
//  componentPool.h
//  CitadelEngine
//
//  Created by Stephanie Barrett on 2022-12-09.
//  Copyright © 2022 Floating Citadel Games. All rights reserved.
//
#pragma once

#include "entity.h"

namespace citadel
{
	namespace ecs
	{
		const EntityID MAX_ENTITIES = 1024;

		class ComponentPool
		{
		protected:
			char* m_pData{ nullptr };
			EntityIndex m_size{ 0 };

		public:
			ComponentPool(EntityIndex size);
			~ComponentPool();

			inline void* get(EntityID id)
			{
				// looking up the component at the desired index
				return m_pData + Entity::GetEntityIndex(id) * m_size;
			}

		}; // class ComponentPool
	} // namespace ecs
} // namespace citadel
