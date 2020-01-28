
#ifndef __UPDATEABLE_H__
#define __UPDATEABLE_H__

namespace citadel
{
    
    class ITickable
    {
    public:
        virtual void tick(const Time & deltaTime) = 0;
        
    }; // class IUpdateable
    
}; // namespace citadel


#endif // __UPDATEABLE_H__
