//
//  GUIPanel.hpp
//
//
//  Created by Norman van der Ploeg on 2017-04-02.
//  Copyright © 2021 Nanzero interactive. All rights reserved.
//

#pragma once

#include "gui/GUIObject.hpp"

namespace citadel::gui {
    
    class GUIPanel : public GUIObject
    {
    private:
        static bool s_registered;

        bool m_bIsMouseDown;
        bool m_bDraggable;
        bool m_bInteractable;
        
//        std::shared_ptr<GUIRenderObject> m_renderObj;
                
    public:
        GUIPanel();
        virtual ~GUIPanel() = default;
        
        /// Factory method
        static std::shared_ptr<GUIObject> build(const Json::Value& objData, std::shared_ptr<GUIEnvironment> pEnv);
        static const std::string getType() { return "GUIPanel"; }
        
        virtual void serialize(Json::Value& jValue) const override;
        virtual void deserialize(const Json::Value& jValue) override;
        
        virtual void draw() const override;
        
        virtual void Tick(const Time& deltaTime) override;
        virtual bool containsPoint(const glm::vec2& point) const override;
        
        virtual void onMouseDragged(const glm::vec2& offset);
        
//        virtual void setRenderObject( std::shared_ptr<GUIRenderObject> renderObj);
    };

}
