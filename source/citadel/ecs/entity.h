#pragma once

#include <vector>
#include <memory>
#include <string>

namespace citadel 
{
    class Component;

    class Entity: public std::enable_shared_from_this<Entity> 
    {
    protected:
        std::vector<std::shared_ptr<Component> > m_components;
    public:
        virtual ~Entity() = default;
        bool HasComponent(const std::string& type) const;

        // return the first component of type
        Component* GetComponent(const std::string& type) const;
        // return all components of type
        std::vector<Component*>  GetComponents(const std::string& type) const;

        void AttachComponent(const std::shared_ptr<Component>& component);
        void DetachComponent(const std::shared_ptr<Component>& component);
    };

}
