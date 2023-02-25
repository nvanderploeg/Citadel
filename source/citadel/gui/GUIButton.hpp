//
//  GUIButton.hpp
//
//
//  Created by Norman van der Ploeg on 2017-04-02.
//  Copyright © 2021 Nanzero interactive. All rights reserved.
//

#pragma once

#include "gui/GUIObject.hpp"

namespace citadel::gui {

class GUIRenderObject;

class GUIButton : public GUIObject
{
private:
    static bool s_registered;

public:
    static const std::string kOnClickEvent;
    enum EButtonState
    {
        BUTTONSTATE_NORMAL = 0,
        BUTTONSTATE_OVER,
        BUTTONSTATE_DOWN,
        BUTTONSTATE_DISABLED,
        
        BUTTONSTATECOUNT
    };
    
protected:
    EButtonState m_currentState = BUTTONSTATE_NORMAL;
    std::function<void()> m_onClick;
    bool m_bIsMouseDown = false;
    std::shared_ptr<GUIRenderObject> m_renderObjs[BUTTONSTATECOUNT]; // Button textures
public:
    GUIButton();
    virtual ~GUIButton() = default;
    
    /// Factory method
    static std::shared_ptr<GUIObject> build(const Json::Value& objData, std::shared_ptr<GUIEnvironment> pEnv);
    static const std::string getType() { return "GUIButton"; }

    virtual void serialize(Json::Value& jValue) const override;
    virtual void deserialize(const Json::Value& jValue) override;
    
    void setButtonState(const EButtonState state, const Json::Value& jValue);
    void setButtonStateRenderObj(const EButtonState state, const std::shared_ptr<GUIRenderObject>& renderObj);
    
    virtual void draw() const override;
    
    virtual void Tick(const Time& deltaTime) override;
    virtual void onMouseButtonDown();
    virtual void onMouseButtonUp();
    virtual void onMouseEntered();
    virtual void onMouseLeft();
    void setOnClick(std::function<void()> clickFunction) { m_onClick = clickFunction; };
    virtual glm::vec2 getSize() const { return m_size; }
    virtual void setSize(const glm::vec2 &size) { m_size = size; }
    
private:
    virtual void setCurrentState(EButtonState state);
    
};

}
