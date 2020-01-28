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
#include "serializer.h"
#include "windowProperties.h"

namespace citadel {

GameConfig::GameConfig(const std::string & path)
{
    windowProperties = std::make_shared<WindowProperties>();
    Json::Value jConfig = Serializer::loadFile(path);
    if(jConfig != Json::nullValue) {
        deserialize(jConfig);
    }
}

void GameConfig::serialize(Json::Value& jValue)
{
    windowProperties->serialize(jValue["windowProperties"]);
    jValue["texturePath"] = texturePath;
    jValue["fontPath"] = fontPath;
    jValue["dataPath"] = dataPath;
}

void GameConfig::deserialize(const Json::Value& jValue)
{
    windowProperties->deserialize(jValue["windowProperties"]);
    texturePath = jValue.get("texturePath", "textures/").asString();
    fontPath = jValue.get("fontPath", "fonts/").asString();
    dataPath = jValue.get("dataPath", "data/").asString();
}
} //namespace citadel
