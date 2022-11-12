#pragma once

#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

#include "cTime.h"
#include "component.h"

namespace citadel {

class Entity {
protected:
    std::vector<Component> m_components;
    
    //Position in 3D space relative to parent
    glm::vec3 m_position;
    
    //Rotations
    glm::quat m_rotation;
    
    //Heirachy
    Entity* m_parent;
    std::vector<Entity*> m_children;
    
public:
    Entity();
    virtual ~Entity() = default;
    
    //Called once on the first frame the entity is added to the scene
    //Setup the object here
    virtual void onStart() = 0;
    
    //Called each frame
    virtual void update(const Time &delta);
    
    //Called once before it is removed from the scene and is expected to deallocate
    virtual void onDestroy() = 0;
    
};


}
