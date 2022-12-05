#pragma once

#include <vector>
#include <memory>
#include <string>

#include "cTime.h"

namespace citadel 
{
    class System
    {
    protected:

        //System gameObjects, must not contain nulls
        std::vector<GameObject*> m_gameObjects;
        
    public:
        System() = default;
        virtual ~System() = default;

        virtual void Update(const Time &delta) = 0;
    };
}