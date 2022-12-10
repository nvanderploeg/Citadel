#include "entity.h"

#include <stdexcept>

#include "component.h"

namespace citadel 
{
    namespace ecs
    {
        //bool Entity::HasComponent(const std::string& type) const
        //{
        //    // GetComponent is doing the same thing, let's use that instead
        //    /*
        //    for (auto& component : m_components) {
        //        if (component->getType() == type) {
        //            return true;
        //        }
        //    }
        //    return false;
        //    */
        //    return (GetComponent(type) != nullptr);
        //}

        //Component* Entity::GetComponent(const std::string& type) const
        //{
        //    for (auto& component : m_components) {
        //        if (component->getType() == type) {
        //            return component.get();
        //        }
        //    }
        //    return nullptr;
        //}

        //std::vector<Component*> Entity::GetComponents(const std::string& type) const
        //{
        //    std::vector<Component*> matchedComponents;
        //    for (auto& component : m_components) {
        //        if (component->getType() == type) {
        //            matchedComponents.emplace_back(component.get());
        //        }
        //    }

        //    return matchedComponents;
        //}

        //void Entity::AttachComponent(const std::shared_ptr<Component>& component)
        //{
        //    if (auto owner = component->owner.lock()) {
        //        throw std::runtime_error("Tried to attach component to entity while it already had an owner");
        //    }
        //    component->owner = shared_from_this();
        //    m_components.emplace_back(component);
        //}

        //void Entity::DetachComponent(const std::shared_ptr<Component>& component)
        //{
        //    auto owner = component->owner.lock();
        //    if (owner.get() != this) {
        //        throw std::runtime_error("Tried to detach a component not owned by this entity");
        //    }
        //    auto it = m_components.begin();
        //    for (; it != m_components.end(); ++it) {
        //        if (component == *it) { break; }
        //    }

        //    if (it == m_components.end()) {
        //        throw std::runtime_error("Couldn't find component in entity to detach");
        //    }
        //    //Techincally slow on a vector, but meh!
        //    m_components.erase(it);
        //}
    } // namespace ecs
} // namespace citadel
