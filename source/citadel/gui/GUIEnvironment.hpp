//
//  GUIEnvironment.hpp

//
//  Created by Norman van der Ploeg on 2017-06-12.
//  Copyright © 2021 Nanzero. All rights reserved.
//

#pragma once

#include <memory>
#include <glm/glm.hpp> //For vec2
#include <system/JSONSerializable.h>
#include <system/tickable.h>

namespace citadel::gui {
    class GUIObject;
    
    class GUIEventListener
    {
    public:
        virtual void onEvent(std::string eventName, std::shared_ptr<GUIObject> source) = 0;
    };
    
    class GUIEnvironment
        : public std::enable_shared_from_this<GUIEnvironment>
        , public ITickable
        , public IJSONSerializable
    {
    private:
        glm::vec2 m_origin = {0,0};
        glm::vec2 m_size = {0,0};
        int m_eventsId = -1;
        std::string m_path;
//        WindowEventHandler * m_handler; ///< Pointer to event handler to register with for mouse/touch events.
        
        std::vector<std::shared_ptr<GUIObject>> m_objects;
        std::map<std::string, Json::Value> m_renderData;
        
        std::map<std::string, std::vector<std::shared_ptr<GUIEventListener>> > m_listeners;
        
        std::shared_ptr<GUIObject> m_currentMouseOverObject;
        std::shared_ptr<GUIObject> m_currentMouseDragObject;
		std::shared_ptr<GUIObject> m_currentFocusedObject;
        glm::vec2 m_lastMousePosition {0,0};
        bool m_bNeedsUpdate = true; ///< Things have changed and children needs to be updated;
        
        GUIEnvironment() = default;
    public:
		~GUIEnvironment();

        static std::shared_ptr<GUIEnvironment> environmentWithFile(const std::string& path, const std::string& file);
        static std::shared_ptr<GUIEnvironment> environmentWithSize(glm::vec2 size);
        static std::shared_ptr<GUIEnvironment> environmentWithBounds(glm::vec4 bounds);
//
//        void attachEventHandler(WindowEventHandler * handler);
//        void detachEventHandler();
        
        void emitEvent(const std::string& eventName, std::shared_ptr<GUIObject> source) const;
        void addEventListener(const std::string& eventName, std::shared_ptr<GUIEventListener> listener);
        void removeEventListener(const std::string& eventName, std::shared_ptr<GUIEventListener> listener);
        
        void draw() const;
        virtual void Tick(const Time& deltaTime) override;

        virtual void serialize(Json::Value& jValue) const override;
        virtual void deserialize(const Json::Value& jValue) override;
        
        void addObject(std::shared_ptr<GUIObject> newObject);
        
        glm::vec2 getLastMousePos() const;
        
        std::shared_ptr<GUIObject> findObject(const std::string& objectID) const;
        std::shared_ptr<GUIObject> findObjectAt(const glm::vec2& point) const;
        Json::Value getRenderData(const std::string& renderID);
        inline void addRenderData(const std::string& renderID, const Json::Value& value) { m_renderData[renderID] = value; };
//
        const glm::vec2 & getSize() const;
        
        void setPath(const std::string & path) { m_path = path; }
        const std::string & getPath() const { return m_path; }
    };
    
}
