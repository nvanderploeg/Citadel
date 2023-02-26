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
        using GUIBuildMap = std::unordered_map<std::string, GUIBuildMethod>;

    private:
        static GUIBuildMap & BuilderMap();

    public:
        GUIFactory() = delete;
        
        static std::shared_ptr<GUIObject> buildObject(const std::string& filePath, std::shared_ptr<GUIEnvironment> pEnv);
        static std::shared_ptr<GUIObject> buildObject(const Json::Value& objData, std::shared_ptr<GUIEnvironment> pEnv);
        
        static bool registerBuilderForClassType(GUIBuildMethod builder, const std::string & type);
    };

} // namespace citadel::gui
