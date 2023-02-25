//
//  GUIConstraint.hpp

//
//  Created by Norman van der Ploeg on 2021-08-02.
//  Copyright © 2021 Nanzero. All rights reserved.
//

#pragma once
#include <memory>

namespace citadel::gui {

class GUIObject;

enum GUIConstraintHook : int
{
    Center = 0,
    Top,
    Bottom,
    Left,
    Right,
    
};

struct GUIConstraint {
    std::weak_ptr<GUIObject> target;
    GUIConstraintHook sourceHook;
    GUIConstraintHook targetHook;
    
    bool operator ==(const GUIConstraint &b) const {
        if (target.lock().get() != b.target.lock().get() ||
            sourceHook != b.sourceHook ||
            targetHook != b.targetHook) {
            return false;
        }
        
        return true;
    }
};

}
