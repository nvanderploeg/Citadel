//
//  GUIObject.hpp
//
//
//  Created by Norman van der Ploeg on 2017-04-02.
//  Copyright © 2021 Nanzero interactive. All rights reserved.
//

#pragma once
#include <memory>
#include <glm/glm.hpp> //For mat

#include <system/JSONSerializable.h>
#include <system/tickable.h>

#include <gui/GUIConstraint.hpp>

namespace citadel::gui
{
    class GUIEnvironment;

    struct GUIZone {
        glm::vec2 origin;
        glm::vec2 position;
        glm::vec2 size;
    };
    
    class GUIObject
        : public std::enable_shared_from_this<GUIObject>
        , public ITickable
        , public IJSONSerializable
	{
    
    protected:
        // Should not be constructed Directly(I think)
        explicit GUIObject(const std::string & ID);
    public:
        virtual ~GUIObject() = default; 
        
        virtual void serialize(Json::Value& jValue) const override;
        virtual void deserialize(const Json::Value& jValue) override;
        
        virtual void draw() const;
        
        virtual void Tick(const Time& deltaTime) override;
        
        virtual bool containsPoint(const glm::vec2& point) const;
        
//		virtual void onTextEntered(const sf::Event& event) {}
//		virtual void onMouseButtonDown() {}
//        virtual void onMouseButtonUp() {}
//        virtual void onMouseEntered() {}
//        virtual void onMouseLeft() {}
//        virtual void onMouseDragged(const glm::vec2 & offset) {}
        
        inline bool isActive() const { return m_bIsActive; }
		inline bool isEnabled() const { return m_bIsEnabled; }
        inline bool isVisible() const { return m_bIsVisible; }

		inline void setActive(bool active) { m_bIsActive = active; }
		inline void setEnabled(bool enabled) { m_bIsEnabled = enabled; }
		inline void setVisible(bool visible) { m_bIsVisible = visible; }

        inline void setNeedsUpdate(bool needsUpdate = true) { m_bNeedsUpdate = needsUpdate; }
        inline bool needsUpdate() const { return m_bNeedsUpdate; }
        
        void setWorldZone(const GUIZone& zone);
        GUIZone calculateSubWorld();
        
        inline glm::vec2 getWorldPosition() const { return m_worldZone.origin + m_position; }
		inline glm::vec2 getPosition() const { return m_position; }
		inline void setPosition(const glm::vec2& position) { m_position = position; m_bNeedsUpdate = true; }
        
        inline glm::vec2 getSize() const { return m_size; }
        inline void setSize(const glm::vec2& size) { m_size = size; m_bNeedsUpdate = true; }

        inline void setGUIEnvironment(std::shared_ptr<GUIEnvironment> pEnv) { m_env = pEnv; }
        inline std::shared_ptr<GUIEnvironment> getGUIEnvironment() { return m_env; }
        
        void addConstraint(const GUIConstraint& constraint);
        void removeConstraint(const GUIConstraint& constraint);
        
        void addChild(std::shared_ptr<GUIObject> newChild);
        void addChild(std::string file);
        void addChild(Json::Value jValue);
        
        bool removeChild(const std::string& ID);
        
        std::shared_ptr<GUIObject> findObjectAt(const glm::vec2 & point);
		std::shared_ptr<GUIObject> findChild(const std::string & ID) const;

		inline const std::string& ID() const { return m_ID; }

        static bool sortFunction(std::shared_ptr<GUIObject> a, std::shared_ptr<GUIObject> b);
        
        virtual bool respondsToEvent(std::string eventName) { return false; }
        virtual void onActionEvent(std::string eventName, std::shared_ptr<GUIObject> emitter);
            
    private:
        bool m_bNeedsUpdate; ///< Flag if position is updated and needs to propegate to it's children;

    protected:
        bool m_bIsActive = true; ///< Controls whether the object and all children received input / ticks
        bool m_bIsVisible = true; ///< Controls the visibility of the shape. If false, the object, and all children will not be rendered.
		bool m_bIsEnabled = true; ///< Controls whether an object can be interacted with
        
        std::shared_ptr<GUIEnvironment> m_env; ///< Reference to the environment it lives, used to propogate events
        
        std::string m_ID; /// and String ID to distinguish an object from other objects.
        ///
        glm::vec2 m_size; ///< Size of the object in points
        glm::vec2 m_position; ///< Position of the object Relative to the TL of the WorldZone Before Jutification
        int m_depth; ///< Specifies the object depth value, used to sort children higher numbers drawn on top of lower;
        
        GUIZone m_worldZone; ///< The ScreenSpace Area in which this object may exist. (may be Subject to culling)

        std::vector<GUIConstraint> m_constraints;
		std::vector<std::shared_ptr<GUIObject>> m_children;
        
//        std::map<std::string, std::unique_ptr<GUIActionTrigger> > m_triggers;
        
//        GameEventHandler<GameEvent<Json::Value> > m_gameEventHandler;
        
	}; // class UIObject
}

