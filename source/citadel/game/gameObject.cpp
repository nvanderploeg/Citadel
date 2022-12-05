#include "gameObject.h"

namespace citadel {

GameObject::GameObject()
:m_position({0,0,0}),m_rotation(glm::identity<glm::quat>())
{

}

void GameObject::update(const Time &delta)
{
    for (auto& child : m_children) {
        child->update(delta);
    }
}

}