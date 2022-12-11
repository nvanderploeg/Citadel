//
//  sceneView.h
//  CitadelEngine
//
//  Created by Stephanie Barrett on 2022-12-09.
//  Copyright © 2022 Floating Citadel Games. All rights reserved.
//
#pragma once

#include "entity.h"

#include "scene.h"

namespace citadel
{
	namespace ecs
	{

		template<typename... ComponentTypes>
		class SceneView
		{
        protected:
            Scene* m_pScene{ nullptr };
            ComponentMask m_componentMask;
            bool m_all{ false };

        public:
            SceneView(Scene* scene)
                : m_pScene(scene)
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
                Scene* m_pScene{ nullptr };
                ComponentMask m_componentMask;
                bool m_all{ false };
                size_t m_index;

                bool ValidIndex()
                {
                    return
                        // It's a valid entity ID
                        Entity::IsEntityValid(m_pScene->entities[m_index].id) &&
                        // It has the correct component mask
                        (m_all || m_componentMask == (m_componentMask & m_pScene->entities[m_index].mask));
                }

            public:
                Iterator(Scene* pScene, EntityIndex index, ComponentMask mask, bool all)
                    : m_pScene(pScene)
                    , m_index(index)
                    , m_componentMask(mask)
                    , m_all(all)
                {
                }

                EntityID operator*() const
                {
                    // give back the entityID we're currently at
                    return m_pScene->entities[m_index].id;
                }

                bool operator==(const Iterator& other) const
                {
                    // Compare two iterators
                    return m_index == other.m_index || m_index == m_pScene->entities.size();
                }

                bool operator!=(const Iterator& other) const
                {
                    // Similar to above
                    return m_index != other.m_index && m_index != m_pScene->entities.size();
                }

                Iterator& operator++()
                {
                    // Move the iterator forward
                    do
                    {
                        m_index++;
                    } while (m_index < m_pScene->entities.size() && !ValidIndex());
                    return *this;
                }
            };

            const Iterator begin() const
            {
                // Give an iterator to the beginning of this view
                int firstIndex = 0;
                while (firstIndex < m_pScene->entities.size() &&
                    (m_componentMask != (m_componentMask & m_pScene->entities[firstIndex].mask)
                        || !Entity::IsEntityValid(m_pScene->entities[firstIndex].id)))
                {
                    ++firstIndex;
                }
                return Iterator(m_pScene, firstIndex, m_componentMask, m_all);
            }

            const Iterator end() const
            {
                // Give an iterator to the end of this view 
                return Iterator(m_pScene, EntityIndex(m_pScene->entities.size()), m_componentMask, m_all);
            }

		}; // class SceneView
	} // namespace ecs
} // namespace citadel