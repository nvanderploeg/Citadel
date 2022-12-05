#include "entity.h"

#include <stdexcept>

#include "component.h";

namespace citadel 
{

    bool Entity::hasComponent(std::string type) const
    {
        for (auto& component : m_components) {
            if (component->getType() == type) {
                return true;
            }
        }
        return false;
    }
        
    std::vector<Component*> Entity::getComponents(std::string type) const
    {
        std::vector<Component*> matchedComponents;
        for (auto& component : m_components) {
            if (component->getType() == type) {
                matchedComponents.emplace_back(component.get());
            }
        }

        return matchedComponents;
    }

    void Entity::attachComponent(std::unique_ptr<Component>& component)
    {
        if (auto owner = component->owner.lock()) {
            throw std::runtime_error("Tried to attach component to entity while it already had an owner");
        }
        component->owner = shared_from_this();
        m_components.emplace_back(component);
    }

    void Entity::detachComponent(Component* component)
    {
        auto owner = component->owner.lock();
        if (owner.get() != this) {
            throw std::runtime_error("Tried to detach a component not owned by this entity");
        }
        auto it = m_components.begin();
        for (; it != m_components.end(); ++it) {
            if (component == it->get()) { break; }
        }

        if (it == m_components.end()) {
            throw std::runtime_error("Couldn't find component in entity to detach");
        }
        //Techincally slow on a vector, but meh!
        m_components.erase(it);
    }

}
