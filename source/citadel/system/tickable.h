
#ifndef __UPDATEABLE_H__
#define __UPDATEABLE_H__

#include "citadel/system/cTime.h"

namespace citadel
{
    
    class ITickable
    {
    public:
        virtual void Tick(const Time& deltaTime) = 0;
        
    }; // class ITickable
    
}; // namespace citadel


#endif // __UPDATEABLE_H__
