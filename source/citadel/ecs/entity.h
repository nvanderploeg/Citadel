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
        std::vector<std::unique_ptr<Component> > m_components;
    public:
        virtual ~Entity() = default;
        bool hasComponent(std::string type) const;
        std::vector<Component*>  getComponents(std::string type) const;

        void attachComponent(std::unique_ptr<Component>& component);
        void detachComponent(Component* component);
    };

}
