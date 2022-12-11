
#pragma once

#include <vector>
#include <memory>
#include <optional>

#include "cTime.h"

#include "entity.h"

namespace citadel 
{

    class GameObject// : public Entity 
    {
    protected:
        //Heirachy
        //object's Parent, may be null
        GameObject* m_parent;

        //Object's children, must not be null
        std::vector<GameObject*> m_children;

        //TransformComponent* m_transform;
        
        //Position in 3D space relative to parent
        //glm::vec3 m_position = {0,0,0};
        
        //Rotations
        //glm::quat m_rotation = glm::identity<glm::quat>();
        

        bool m_initilized = false;
        bool m_active = true;

        //TODO: consider building out a cache system to pass various values down to it's children.
        //We might accomplish this using a dirty flag, doing extra work on the update method if 
        //The object was dirty, for example, if the object is moved, all it's children will need
        //An updated world transform to be able to correctly render in the right position
        //If we don't use such a cache, it has to calculate it every frame which can become expensive
        //if objects have a lot of ancestors.
        //bool m_dirty();
        //void make_dirty(); //Also dirties children.
    public:
        GameObject() = default;
        virtual ~GameObject() = default;
        
        //Called once on the first frame after the entity is added to the scene
        //Use this method to intialize data and configure components before first use
        virtual void onEnteredScene();
        
        //Called each frame
        virtual void Update(const Time &delta);
        
        //Called once before it is removed from the scene and is expected to deallocate
        //Use this method to teardown components or finalize data.
        virtual void onDestroyed();

        bool isInitialized() const { return m_initilized; }

        //returns the active flag of this object
        bool isActiveSelf() const { return m_active; }

        //Resolves if the object's active state (including parents)
        bool isActive() const;
        
    };

}