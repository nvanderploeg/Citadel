#pragma once

#include <vector>
#include <memory>
#include <string>

#include "component.h"

namespace citadel {

class Entity {
protected:
    std::vector<std::shared_ptr<Component> > m_components;
public:
    virtual ~Entity() = default;
    bool hasComponent(std::string type) const;
    std::vector<std::shared_ptr<Component> >  getComponents(std::string type) const;
};

}
