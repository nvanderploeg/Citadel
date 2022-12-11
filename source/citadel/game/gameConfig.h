//
//  gameConfig.hpp
//  CitadelEngine
//
//  Created by Norman van der Ploeg on 2020-01-17.
//  Copyright © 2020 Floating Citadel Games. All rights reserved.
//

#ifndef gameConfig_hpp
#define gameConfig_hpp

#include "JSONSerializable.h"

namespace citadel {

class WindowProperties;
    
class GameConfig : public IJSONSerializable
{
public:
    std::shared_ptr<WindowProperties> windowProperties;
    std::string texturePath;
    std::string fontPath;
    std::string dataPath;

    std::filesystem::path filepath;

public:
    GameConfig(const std::filesystem::path& path);

    bool Save();

    virtual void serialize(Json::Value& jValue);
    virtual void deserialize(const Json::Value& jValue);
};

} // namespace Citadel

#endif /* gameConfig_hpp */
