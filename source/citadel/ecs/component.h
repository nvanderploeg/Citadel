#pragma once

namespace citadel {

class Component {
    
public:
    
    //Called once on the first frame the component is added to the scene
    //Setup the object here
    virtual void onStart() = 0;
    
    //Called each frame
    virtual void update(const Time &delta) = 0;
    
    //Called once before it is removed from the scene and is expected to deallocate
    virtual void onDestroy() = 0;
    
};


}

