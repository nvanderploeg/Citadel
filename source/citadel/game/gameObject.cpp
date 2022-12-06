
#include "gameObject.h"
#include <iostream>

namespace citadel 
{
    void GameObject::onEnteredScene()
    {
        //Use this opportunity to load data and configure components before first use

        m_transform = std::make_shared<TransformComponent>();
        AttachComponent(std::dynamic_pointer_cast<Component>(m_transform));
        
        //Finally we are ready to use by the rest of the game systems
        m_initilized = true;
    }

    void GameObject::onDestroyed() 
    {
        //Mark ourself unavailable to other game systems
        m_initilized = false;

        //Use this opportunity to teardown components or save data.
    }

    void GameObject::Update(const Time &delta)
    {
        if (!isActive()) {
            return;
        }

        for (auto& child : m_children) {
            child->Update(delta);
        }

        if (m_transform)
            std::cout << "{" << m_transform->position.x << ", " << m_transform->position.y << "}\n";
    }

    bool GameObject::isActive() const {
        if (!m_active) { return false; }
        if (m_parent) { return m_parent->isActive(); }
        return true;
    }

}