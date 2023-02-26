//
//  GUIPanel.cpp
//
//
//  Created by Norman van der Ploeg on 2017-04-02.
//  Copyright © 2021 Nanzero interactive. All rights reserved.
//

#include <gui/GUIPanel.hpp>

#include <gui/GUIEnvironment.hpp>
#include <gui/GUIRenderObject.hpp>
#include <gui/GUIFactory.hpp>

namespace citadel::gui
{

    bool GUIPanel::s_registered = GUIFactory::registerBuilder<GUIPanel>(GUIPanel::build, GUIPanel::getType());
    
    GUIPanel::GUIPanel()
        : GUIObject(getType())
        , m_bIsMouseDown(false)
        , m_bDraggable(true)
        , m_bInteractable(true)
        , m_renderObj(nullptr)
    {

    }
    
    std::shared_ptr<GUIObject> GUIPanel::build(const Json::Value& objData, std::shared_ptr<GUIEnvironment> pEnv)
    {
        std::shared_ptr<GUIObject> newPanel(new GUIPanel());
        newPanel->setGUIEnvironment(pEnv);
        newPanel->deserialize(objData);
        return newPanel;
    }

    
    void GUIPanel::serialize(Json::Value& jValue) const
    {
        GUIObject::serialize(jValue);
        jValue["type"] = getType();
        jValue["draggable"] = m_bDraggable;
        jValue["interactable"] = m_bInteractable;
    }
    
    void GUIPanel::deserialize(const Json::Value& jValue)
    {
        GUIObject::deserialize(jValue);
        m_bDraggable = jValue.get("draggable", false).asBool();
        m_bInteractable = jValue.get("interactable", true).asBool();
        
        Json::Value renderValue = jValue.get("renderComponent", Json::nullValue);
        if (renderValue != Json::nullValue) {
            std::string renderID = renderValue.asString();
            Json::Value renderComponent = m_env->getRenderData(renderID);
            if (renderComponent != Json::nullValue) {
                m_renderObj = std::make_shared<GUIRenderObject>();
                m_renderObj->deserialize(renderComponent);
                m_renderObj->setSize(m_size);
            }
        }
    }
    
    void GUIPanel::draw() const
    {
        if (m_renderObj) {
            m_renderObj->draw();
        }
        
        GUIObject::draw();
    }
    
    void GUIPanel::Tick(const Time& deltaTime)
    {
        if (needsUpdate()) {
            if (m_renderObj) {
//                m_renderObj->setBounds(calculateSubWorld().zone);
            }
        }
        
        if (m_renderObj) {
            m_renderObj->Tick(deltaTime);
        }
        
        GUIObject::Tick(deltaTime);
    }
    
    bool GUIPanel::containsPoint(const glm::vec2 & point) const
    {
        if (!m_bInteractable) {
            return false;
        }

        return GUIObject::containsPoint(point);
    }
    
    void GUIPanel::onMouseDragged(const glm::vec2 & offset)
    {
        if (m_bDraggable)
        {
            GUIObject::onActionEvent("__panel_dragged", shared_from_this());
            m_position += offset;
            setNeedsUpdate();
        }
    }
    
    void GUIPanel::setRenderObject(std::shared_ptr<GUIRenderObject> renderObj)
    {
        if (nullptr == renderObj)
            return; // Throw?? Assert???

        m_renderObj = renderObj;
        m_renderObj->setSize(m_size);
        setNeedsUpdate();
    }
    
} //namespace citadel::gui
