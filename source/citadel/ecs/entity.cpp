#include "entity.h"

namespace citadel {
    
bool Entity::hasComponent(std::string type) const
{
    for (auto& compoent : m_components) {
        if (compoent->getType() == type) {
            return true;
        }
    }
    return false;
}
    
std::vector<std::shared_ptr<Component> >  Entity::getComponents(std::string type) const
{
    std::vector<std::shared_ptr<Component> > components;
     for (auto& compoent : m_components) {
        if (compoent->getType() == type) {
            components.emplace_back(compoent);
        }
    }

    return components;
}

}
