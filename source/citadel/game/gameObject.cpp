#include "gameObject.h"

namespace citadel 
{
    void GameObject::onStart() 
    {
        //Find all systems 

        //Finally we are ready to use by the rest of the game systems
        m_initilized = true;
    }

    void GameObject::onDestroy() 
    {
        //Mark ourself unavailable to other game systems
        m_initilized = false;

        //
    }

    void GameObject::update(const Time &delta)
    {
        for (auto& child : m_children) {
            child->update(delta);
        }
    }

}