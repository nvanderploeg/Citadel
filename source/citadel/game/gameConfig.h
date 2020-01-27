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
#include "JSONSerializable.h"
#include "citadel/system/windowProperties.h"

namespace citadel {
    
    class GameConfig : public IJSONSerializable
    {
    public:
        WindowProperties windowProperties;
        std::string texturePath;
        std::string fontPath;
        std::string dataPath;

    public:
        GameConfig(const std::string & path);

        virtual void serialize(Json::Value & jValue);
        virtual void deserialize(const Json::Value & jValue);
    };
} // namespace Citadel

#endif /* gameConfig_hpp */
