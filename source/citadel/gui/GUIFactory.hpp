//
//  GUIFactory.hpp

//
//  Created by Norman van der Ploeg on 2017-07-16.
//  Copyright © 2021 Nanzero. All rights reserved.
//

#pragma once
#include <memory>
#include <unordered_map>
#include <json/json.h>

namespace citadel::gui 
{
    class GUIEnvironment;
    class GUIObject;

    class GUIFactory
	{
    public:
        using GUIBuildMethod = std::shared_ptr<GUIObject>(*)(const Json::Value&, std::shared_ptr<GUIEnvironment>);
    private:
        std::unordered_map<std::string, GUIBuildMethod> m_builderMap;
        GUIFactory() = default;
    public:
        static GUIFactory* Shared();
        static std::shared_ptr<GUIObject> buildObject(const std::string& filePath, std::shared_ptr<GUIEnvironment> pEnv);
        static std::shared_ptr<GUIObject> buildObject(const Json::Value& objData, std::shared_ptr<GUIEnvironment> pEnv);
        
        template<typename T>
        static bool registerBuilder(GUIBuildMethod builder, const std::string & type) {
             auto buildMap = GUIFactory::Shared()->m_builderMap;
            buildMap[type] = builder;
        }
    };

} // namespace citadel::gui
