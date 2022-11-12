#include "entity.h"


namespace citadel {

void Entity::update(const Time &delta)
{
    for (auto& child : m_children) {
        child->update(delta);
    }
}



}
