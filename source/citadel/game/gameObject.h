
#pragma once

#include <vector>
#include <memory>
#include <optional>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

#include "cTime.h"

#include "entity.h"

namespace citadel 
{

    class GameObject : public Entity 
    {
    protected:
        //Heirachy
        std::optional<GameObject*> m_parent;
        std::vector<GameObject*> m_children;
        
        //Position in 3D space relative to parent
        glm::vec3 m_position = {0,0,0};
        
        //Rotations
        glm::quat m_rotation = glm::identity<glm::quat>();
        

        bool m_initilized = false;

    public:
        GameObject() = default;
        virtual ~GameObject() = default;
        
        //Called once on the first frame the entity is added to the scene
        //Setup the object here
        virtual void onStart();
        
        //Called each frame
        virtual void update(const Time &delta);
        
        //Called once before it is removed from the scene and is expected to deallocate
        virtual void onDestroy();
        
    };

}