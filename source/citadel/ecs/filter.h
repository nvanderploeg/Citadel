//
//  filter.h
//  CitadelEngine
//
//  Created by Stephanie Barrett on 2022-12-09.
//  Copyright © 2022 Floating Citadel Games. All rights reserved.
//
#pragma once

#include "component.h"
#include "entity.h"

namespace citadel
{
	namespace ecs
	{
        class Registry;

		template<typename... ComponentTypes>
		class Filter
		{
        protected:
            ComponentMask m_componentMask;
            Registry* m_pRegistry{ nullptr };
            bool m_all{ false };

        public:
            Filter(Registry* pRegistry)
                : m_pRegistry(pRegistry)
                , m_all(false)
            {
                if (sizeof...(ComponentTypes) == 0)
                {
                    m_all = true;
                }
                else
                {
                    // Unpack the template parameters into an initializer list
                    ComponentID componentIds[] = { 0, Component::GetID<ComponentTypes>() ... };
                    for (int i = 1; i < (sizeof...(ComponentTypes) + 1); ++i)
                    {
                        m_componentMask.set(componentIds[i]);
                    }
                }
            }

            class Iterator
            {
            private:
                EntityIndex m_index;
                ComponentMask m_componentMask;
                Registry* m_pRegistry{ nullptr };
                bool m_all{ false };

            public:
                Iterator(Registry* pRegistry, EntityIndex index, ComponentMask mask, bool all)
                    : m_pRegistry(pRegistry)
                    , m_index(index)
                    , m_componentMask(mask)
                    , m_all(all)
                {
                    // empty
                }

                EntityID operator*() const
                {
                    return m_pRegistry->entities[m_index].id;
                }

                bool operator==(const Iterator& other) const
                {
                    return m_index == other.m_index || m_index == m_pRegistry->entities.size();
                }

                bool operator!=(const Iterator& other) const
                {
                    return m_index != other.m_index && m_index != m_pRegistry->entities.size();
                }

                Iterator& operator++()
                {
                    do
                    {
                        m_index++;
                    } while (m_index < m_pRegistry->entities.size() && !(Entity::IsEntityValid(m_pRegistry->entities[m_index].id) && (m_all || m_componentMask == (m_componentMask & m_pRegistry->entities[m_index].mask))));
                    return *this;
                }
            };

            const Iterator begin() const
            {
                int firstIndex = 0;
                while (firstIndex < m_pRegistry->entities.size() && (m_componentMask != (m_componentMask & m_pRegistry->entities[firstIndex].mask) || !Entity::IsEntityValid(m_pRegistry->entities[firstIndex].id)))
                {
                    ++firstIndex;
                }
                return Iterator(m_pRegistry, firstIndex, m_componentMask, m_all);
            }

            const Iterator end() const
            {
                return Iterator(m_pRegistry, EntityIndex(m_pRegistry->entities.size()), m_componentMask, m_all);
            }

		}; // class Filter
	} // namespace ecs
} // namespace citadel