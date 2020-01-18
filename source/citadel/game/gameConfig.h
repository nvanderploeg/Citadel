//
//  gameConfig.hpp
//  CitadelEngine
//
//  Created by Norman van der Ploeg on 2020-01-17.
//  Copyright © 2020 Floating Citadel Games. All rights reserved.
//

#ifndef gameConfig_hpp
#define gameConfig_hpp
#include <string>

namespace citadel {
    
class GameConfig {
public:
    GameConfig(const std::string &path);
    int width;
    int height;
    std::string title;
};

} // namespace Citadel

#endif /* gameConfig_hpp */
