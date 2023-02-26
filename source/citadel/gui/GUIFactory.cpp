//
//  GUIFactory.cpp

//
//  Created by Norman van der Ploeg on 2017-07-16.
//  Copyright © 2021 Nanzero. All rights reserved.
//

#include <gui/GUIFactory.hpp>

#include <iostream>
#include <memory>
#include <thread>

#include <system/serializer.h>

#include <gui/GUIEnvironment.hpp>
#include <gui/GUIObject.hpp>


namespace {

std::unique_ptr<citadel::gui::GUIFactory> g_factory = nullptr;
std::mutex g_factoryMutex;
}

namespace citadel::gui
{

    GUIFactory* GUIFactory::Shared() {
        std::lock_guard<std::mutex> guard(g_factoryMutex);
        if (!g_factory) {
            g_factory = std::unique_ptr<GUIFactory>( new GUIFactory());
        }
        return g_factory.get();
    }

    std::shared_ptr<GUIObject> GUIFactory::buildObject(const std::string& filePath, std::shared_ptr<GUIEnvironment> pEnv)
    {
        Json::Value jRoot = Serializer::loadFile(filePath);
        if (jRoot == Json::nullValue) {
            return nullptr;
        }
        
        return buildObject(jRoot, pEnv);
    }

    std::shared_ptr<GUIObject> GUIFactory::buildObject(const Json::Value& json, std::shared_ptr<GUIEnvironment> pEnv)
    {
        auto buildMap = GUIFactory::Shared()->m_builderMap;
        Json::Value jRoot = json;
        if (jRoot.isString()) {
            jRoot  = Serializer::loadFile(pEnv->getPath() + jRoot.asString());
        }
        
        if (jRoot.isObject()) {
            Json::Value typeValue = jRoot["type"];
            if (typeValue != Json::nullValue) {
                if (auto it = buildMap.find(typeValue.asString()); it != buildMap.end()) {
                    return it->second(jRoot, pEnv);
                }
				else {
					std::cout << "Didn't find factory for: " << typeValue.asString() << std::endl;
				}
            }
        }
        
        return nullptr;
    }
    
}
