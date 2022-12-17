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
    const std::string DEFAULT_MODELPATH = "models/";
    const std::string DEFAULT_SHADERPATH = "shaders/";
    const std::string DEFAULT_TEXTUREPATH = "textures/";
    const std::string DEFAULT_FONTPATH = "fonts/";
    const std::string DEFAULT_DATAPATH = "data/";
}

namespace citadel
{
    GameConfig::GameConfig(const std::filesystem::path& path)
    {
        filepath = path;
        windowProperties = std::make_shared<WindowProperties>();
        Json::Value jConfig = Serializer::loadFile(filepath);
        if (jConfig == Json::nullValue)
        {
            modelPath = DEFAULT_MODELPATH;
            shaderPath = DEFAULT_SHADERPATH;
            texturePath = DEFAULT_TEXTUREPATH;
            fontPath = DEFAULT_FONTPATH;
            dataPath = DEFAULT_DATAPATH;

            // TODO: logger
            std::cout << "WARNING: Configuration file not found; using default values." << std::endl;
            Serializer::serialize(this, filepath);
            std::cout << "INFO: Generated default game config at: " << filepath << std::endl;
        }
        else
        {
            deserialize(jConfig);
        }
    }

    bool GameConfig::Save()
    {
        return Serializer::serialize(this, filepath);
    }

    void GameConfig::serialize(Json::Value& jValue)
    {
        windowProperties->serialize(jValue["windowProperties"]);
        jValue["modelPath"] = modelPath;
        jValue["shaderPath"] = shaderPath;
        jValue["texturePath"] = texturePath;
        jValue["fontPath"] = fontPath;
        jValue["dataPath"] = dataPath;
    }

    void GameConfig::deserialize(const Json::Value& jValue)
    {
        windowProperties->deserialize(jValue["windowProperties"]);
        modelPath = jValue.get("modelPath", DEFAULT_MODELPATH).asString();
        shaderPath = jValue.get("shaderPath", DEFAULT_SHADERPATH).asString();
        texturePath = jValue.get("texturePath", DEFAULT_TEXTUREPATH).asString();
        fontPath = jValue.get("fontPath", DEFAULT_FONTPATH).asString();
        dataPath = jValue.get("dataPath", DEFAULT_DATAPATH).asString();
    }
} //namespace citadel
