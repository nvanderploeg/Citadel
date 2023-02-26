//
//  GUIFactory.cpp

//
//  Created by Norman van der Ploeg on 2017-07-16.
//  Copyright © 2021 Nanzero. All rights reserved.
//

#include <gui/GUIFactory.hpp>

#include <iostream>

#include <system/serializer.h>

#include <gui/GUIEnvironment.hpp>
#include <gui/GUIObject.hpp>

namespace citadel::gui
{

    GUIFactory::GUIBuildMap& GUIFactory::BuilderMap()
    {
        static GUIBuildMap s_builderMap;
        return s_builderMap;
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
        Json::Value jRoot = json;
        if (jRoot.isString()) {
            jRoot  = Serializer::loadFile(pEnv->getPath() + jRoot.asString());
        }
        
        if (jRoot.isObject()) {
            Json::Value typeValue = jRoot["type"];
            if (typeValue != Json::nullValue) {
                if (auto it = BuilderMap().find(typeValue.asString()); it != BuilderMap().end()) {
                    return it->second(jRoot, pEnv);
                }
				else {
					std::cout << "Didn't find factory for" << typeValue.asString() << std::endl;
				}
            }
        }
        
        return nullptr;
    }
    
    bool GUIFactory::registerBuilderForClassType(GUIFactory::GUIBuildMethod buildMethod, const std::string & type)
    {
        if (auto it = BuilderMap().find(type); it == BuilderMap().end()) {
			std::cout << "Registered factory method for " << type << std::endl;
            BuilderMap()[type] = buildMethod;
            return true;
        }
        return false;
    }
    
}
