//
//  gameConfig.cpp
//  CitadelEngine
//
//  Created by Norman van der Ploeg on 2020-01-17.
//  Copyright © 2020 Floating Citadel Games. All rights reserved.
//

#include <iostream>
#include <memory>
#include <cstdlib>
#include <filesystem>
#include "gameConfig.h"
#include "serializer.h"
#include "windowProperties.h"

namespace
{
    const std::string DEFAULT_TEXTUREPATH = "textures/";
    const std::string DEFAULT_FONTPATH = "fonts/";
    const std::string DEFAULT_DATAPATH = "data/";
    const std::string DEFAULT_INPUTCONTEXT = "inputContext.cfg";
}

namespace citadel {

GameConfig::GameConfig(const std::filesystem::path& path)
{
    windowProperties = std::make_shared<WindowProperties>();
    Json::Value jConfig = Serializer::loadFile(path);
    if (jConfig == Json::nullValue)
    {
        texturePath = DEFAULT_TEXTUREPATH;
        fontPath = DEFAULT_FONTPATH;
        dataPath = DEFAULT_DATAPATH;
        inputContext = DEFAULT_INPUTCONTEXT;

        // TODO: logger
        std::cout << "WARNING: Configuration file not found; using default values." << std::endl;
        Serializer::serialize(this, path);
        std::cout << "INFO: Generated default game config at: " << path << std::endl;
    }
    else
    {
        deserialize(jConfig);
    }
}

void GameConfig::serialize(Json::Value& jValue)
{
    windowProperties->serialize(jValue["windowProperties"]);
    jValue["texturePath"] = texturePath;
    jValue["fontPath"] = fontPath;
    jValue["dataPath"] = dataPath;
    jValue["inputContext"] = inputContext;
}

void GameConfig::deserialize(const Json::Value& jValue)
{
    windowProperties->deserialize(jValue["windowProperties"]);
    texturePath = jValue.get("texturePath", DEFAULT_TEXTUREPATH).asString();
    fontPath = jValue.get("fontPath", DEFAULT_FONTPATH).asString();
    dataPath = jValue.get("dataPath", DEFAULT_DATAPATH).asString();
    inputContext = jValue.get("inputContextPath", DEFAULT_INPUTCONTEXT).asString();
}
} //namespace citadel
