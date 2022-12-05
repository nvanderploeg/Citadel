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
        bool HasComponent(std::string type) const;
        std::vector<Component*>  GetComponents(std::string type) const;

        void AttachComponent(const std::shared_ptr<Component>& component);
        void DetachComponent(const std::shared_ptr<Component>& component);
    };

}
