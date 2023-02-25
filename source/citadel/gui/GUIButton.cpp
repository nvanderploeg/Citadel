//
//  GUIButton.cpp
//
//
//  Created by Norman van der Ploeg on 2017-04-02.
//  Copyright © 2021 Nanzero interactive. All rights reserved.
//

#include <gui/GUIButton.hpp>
#include <gui/GUIEnvironment.hpp>
#include <gui/GUIRenderObject.hpp>

namespace citadel::gui
{
//    bool GUIButton::s_registered = GUIFactory::registerBuilderForClassType(GUIButton::build, GUIButton::getType());

    const std::string GUIButton::kOnClickEvent = "onClickedEvent";

	GUIButton::GUIButton(): GUIObject(getType()) { }

    std::shared_ptr<GUIObject> GUIButton::build(const Json::Value& objData, std::shared_ptr<GUIEnvironment> pEnv)
    {
        auto newButton = std::make_shared<GUIButton>();
        
        newButton->setGUIEnvironment(pEnv);
        newButton->deserialize(objData);
        
		return newButton;
    }

    void GUIButton::serialize(Json::Value& jValue) const
    {
        GUIObject::serialize(jValue);
        jValue["type"] = getType();
        jValue["states"]["mousedown"]["color"] = 0x0000ffff;
    }
    
    void GUIButton::deserialize(const Json::Value& jValue)
    {
        GUIObject::deserialize(jValue);
      
        Json::Value stateValues = jValue["states"];
        if (stateValues != Json::nullValue)  {
            setButtonState(BUTTONSTATE_OVER, stateValues["mouseOver"]);
            setButtonState(BUTTONSTATE_DOWN, stateValues["mouseDown"]);
            setButtonState(BUTTONSTATE_NORMAL, stateValues["default"]);
            setButtonState(BUTTONSTATE_DISABLED, stateValues["disabled"]);
        }
    }


    void GUIButton::setButtonState(const EButtonState state, const Json::Value& jValue)
    {
        if (jValue == Json::nullValue) {
            return;
        }
        
        Json::Value renderValue = jValue["renderComponent"];
        if (renderValue != Json::nullValue) {
            std::string renderID = renderValue.asString();
//            Json::Value renderComponent = m_env->getRenderData(renderID);
//            if (renderComponent != Json::nullValue)
//            {
//                auto renderObjs = std::make_shared<GUIRenderObject>();
//                renderObjs->deserialize(renderComponent);
//                renderObjs->setSize(m_size);
//                setButtonStateRenderObj(state, renderObjs);
//            }
        }
    }

    void GUIButton::setButtonStateRenderObj(const EButtonState state, const std::shared_ptr<GUIRenderObject>& renderObj)
    {
        m_renderObjs[state] = renderObj;
        setNeedsUpdate();
    }

    void GUIButton::draw() const
    {
		if (m_renderObjs[m_currentState]) {
			m_renderObjs[m_currentState]->draw();
		}
        GUIObject::draw();
    }
    
    void GUIButton::Tick(const Time& deltaTime)
    {
		if (m_bIsEnabled == false && m_currentState != BUTTONSTATE_DISABLED)
		{
			m_currentState = BUTTONSTATE_DISABLED;
            GUIObject::onActionEvent("__button_disabled", shared_from_this());
		}
		else if (m_bIsEnabled == true && m_currentState == BUTTONSTATE_DISABLED)
		{
			m_currentState = BUTTONSTATE_NORMAL;
            GUIObject::onActionEvent("__button_enabled", shared_from_this());
		}
        
        if (m_renderObjs[m_currentState]) {
            m_renderObjs[m_currentState]->Tick(deltaTime);
        }
        GUIObject::Tick(deltaTime);
    }

    void GUIButton::setCurrentState(EButtonState state)
    {
        m_currentState = state;
        if (nullptr != m_renderObjs[m_currentState])
        {
//            m_renderObjs[m_currentState]->setBounds(calculateSubWorld().zone);
            m_renderObjs[m_currentState]->Tick(Time());
        }
    }

    void GUIButton::onMouseButtonDown()
    {
        if (m_currentState == BUTTONSTATE_DISABLED) {
            return;
        }

		m_bIsMouseDown = true;
        setCurrentState(BUTTONSTATE_DOWN);
        GUIObject::onActionEvent("__button_down", shared_from_this());
    }
    
    void GUIButton::onMouseButtonUp()
    {
        if (m_currentState == BUTTONSTATE_DISABLED) {
            return;
        }
        
        GUIObject::onActionEvent("__button_up", shared_from_this());
        
		if (m_bIsMouseDown) {
            if (m_onClick)
                m_onClick();
            
//            if (m_env)
//                m_env->emitEvent(kOnClickEvent, shared_from_this());
//            GameEvent<Json::Value> clickEvent("click", Json::nullValue);
//            m_gameEventHandler.pushEvent(clickEvent);
        }
        
        setCurrentState(BUTTONSTATE_OVER);
        m_bIsMouseDown = false;
    }

    void GUIButton::onMouseEntered()
    {
        if (m_currentState == BUTTONSTATE_DISABLED) {
            return;
        }
        
        GUIObject::onActionEvent("__button_mouseenter", shared_from_this());
        setCurrentState(BUTTONSTATE_OVER);
    }

    void GUIButton::onMouseLeft()
    {
        if (m_currentState == BUTTONSTATE_DISABLED) {
            return;
        }
        GUIObject::onActionEvent("__button_mouseout", shared_from_this());
    
		m_bIsMouseDown = false;
        setCurrentState(BUTTONSTATE_NORMAL);
    }
    
} //namespace citadel::gui
