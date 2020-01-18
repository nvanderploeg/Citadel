//
//  gameConfig.cpp
//  CitadelEngine
//
//  Created by Norman van der Ploeg on 2020-01-17.
//  Copyright © 2020 Floating Citadel Games. All rights reserved.
//

#include <memory>
#include <cstdlib>
#include "gameConfig.h"

namespace citadel {

GameConfig::GameConfig(const std::string &path):width(640) , height(480)
{
    title = "Citadel Game";
}

} //namespace citadel
