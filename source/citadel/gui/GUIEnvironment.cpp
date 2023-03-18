//
//  GUIEnvironment.cpp

//
//  Created by Norman van der Ploeg on 2017-06-12.
//  Copyright © 2021 Nanzero. All rights reserved.
//

#include <gui/GUIEnvironment.hpp>
#include <gui//GUIFactory.hpp>
#include <gui/GUIObject.hpp>

#include <system/serializer.h>


namespace citadel::gui {
    
    GUIEnvironment::~GUIEnvironment()
    {
//		detachEventHandler();
    }
    
    std::shared_ptr<GUIEnvironment> GUIEnvironment::environmentWithFile(const std::string& path, const std::string& file)
    {
//        DEBUG("Loading %s", (path + file).c_str());
        Json::Value jRoot = Serializer::loadFile(path + file);
		if (jRoot != Json::nullValue) {
			std::shared_ptr<GUIEnvironment> anEnvironment(new GUIEnvironment());
            anEnvironment->setPath(path);
			anEnvironment->deserialize(jRoot);
//            DEBUG(" - success.\n");
			return anEnvironment;
		}
//        DEBUG(" - failed.\n");
		return nullptr;
    }

    std::shared_ptr<GUIEnvironment> GUIEnvironment::environmentWithSize(glm::vec2 size)
    {
        std::shared_ptr<GUIEnvironment> anEnvironment(new GUIEnvironment());
        anEnvironment->m_size = size;
        anEnvironment->m_origin = {0,0};
        
        //Add Input hooks here.
        return anEnvironment;
    }
    std::shared_ptr<GUIEnvironment> GUIEnvironment::environmentWithBounds(glm::vec4 bounds)
    {
        std::shared_ptr<GUIEnvironment> anEnvironment(new GUIEnvironment());
        anEnvironment->m_size = {bounds[2], bounds[3]};
        anEnvironment->m_origin = {bounds.x, bounds.y};
        
        return anEnvironment;
    }
//    void GUIEnvironment::attachEventHandler(WindowEventHandler * handler)
//    {
//		static int idCounter = 0;
//        m_handler = handler;
//		if (m_eventsId == -1) m_eventsId = ++idCounter;
//
//		m_handler->registerListener(sf::Event::TextEntered, m_eventsId, [this](const sf::Event& event, void * pData) {
//			if (m_currentFocusedObject) {
//				m_currentFocusedObject->onTextEntered(event);
//			}
//		});
//
//        m_handler->registerListener(sf::Event::MouseMoved, m_eventsId, [this](const sf::Event& event, void * pData) {
//            const sf::Event::MouseMoveEvent& mmEvent = event.mouseMove;
//            glm::vec2 point(mmEvent.x, mmEvent.y);
//            std::shared_ptr<GUIObject> obj = this->findObjectAt(point);
//
//            if (obj != this->m_currentMouseOverObject) {
//                if (obj) {
//                    obj->onMouseEntered();
//                }
//                if (this->m_currentMouseOverObject && m_currentMouseOverObject->isEnabled()) {
//                    this->m_currentMouseOverObject->onMouseLeft();
//                }
//            }
//
//            if (m_currentMouseDragObject) {
//                m_currentMouseDragObject->onMouseDragged(point-m_lastMousePosition);
//            }
//
//            m_lastMousePosition = point;
//            m_currentMouseOverObject = obj;
//        });
//
//        m_handler->registerListener(sf::Event::MouseButtonPressed, m_eventsId, [this](const sf::Event& event, void * pData) {
//            const sf::Event::MouseButtonEvent& mbEvent = event.mouseButton;
//            Vector2i point = Vector2i(mbEvent.x,mbEvent.y);
//            std::shared_ptr<GUIObject> obj = this->findObjectAt(point);
//
//            if (obj) {
//                if (obj != this->m_currentMouseOverObject) {
//                    assert(0);
//                }
//
//                m_currentMouseDragObject = obj;
//
//                if (obj->isEnabled()) {
//					m_currentFocusedObject = obj;
//                }
//            }
//
//            if (m_currentMouseOverObject && m_currentMouseOverObject->isEnabled()) {
//               m_currentMouseOverObject->onMouseButtonDown();
//            }
//
//        });
//
//        m_handler->registerListener(sf::Event::MouseButtonReleased, m_eventsId, [this](const sf::Event& event, void * pData) {
//            const sf::Event::MouseButtonEvent& mbEvent = event.mouseButton;
//
//            Vector2i point = Vector2i(mbEvent.x,mbEvent.y);
//            std::shared_ptr<GUIObject> obj = this->findObjectAt(point);
//            if (obj) {
//                //This Shouldn't Happen!
//                if (obj != this->m_currentMouseOverObject) {
//                    assert(0);
//                }
//            }
//
//            m_currentMouseDragObject = nullptr;
//
//            if (m_currentFocusedObject && obj != m_currentFocusedObject) {
//				m_currentFocusedObject = nullptr;
//            }
//
//            if (m_currentMouseOverObject) {
//                m_currentMouseOverObject->onMouseButtonUp();
//            }
//        });
//    }
//
//    void GUIEnvironment::detachEventHandler()
//    {
//		if (m_handler) {
//			m_handler->deregisterListener(sf::Event::MouseMoved, m_eventsId);
//			m_handler->deregisterListener(sf::Event::MouseButtonPressed, m_eventsId);
//			m_handler->deregisterListener(sf::Event::MouseButtonReleased, m_eventsId);
//			m_handler->deregisterListener(sf::Event::TextEntered, m_eventsId);
//
//			m_handler = NULL;
//			m_eventsId = -1;
//		}
//    }
//
    glm::vec2 GUIEnvironment::getLastMousePos() const
    {
        return m_lastMousePosition;
    }
    
    void GUIEnvironment::emitEvent(const std::string & eventName, std::shared_ptr<GUIObject> source) const
    {
        auto it = m_listeners.find(eventName);
        if (it != m_listeners.end()) {
            auto [name, array] = *it;
            for (auto listener : array) {
                listener->onEvent(name, source);
            }
        }
    }

    void GUIEnvironment::addEventListener(const std::string & eventName, std::shared_ptr<GUIEventListener> listener)
    {
        m_listeners[eventName].push_back(listener);
    }

    void GUIEnvironment::removeEventListener(const std::string & eventName, std::shared_ptr<GUIEventListener> listener)
    {
        auto listenersIt = m_listeners.find(eventName);
        if (listenersIt != m_listeners.end()) {
            auto [name, array] = *listenersIt;
            for (auto it = array.begin(); it != array.end(); it++) {
                if ((*it) == listener) {
                    array.erase(it);
                    break;
                }
            }
        }
    }
    
    void GUIEnvironment::serialize(Json::Value& jValue) const
    {
//        m_origin.serialize(jValue["origin"]);
//        m_size.serialize(jValue["size"]);
//
        jValue["objects"] = Json::arrayValue;

        for (auto object : m_objects) {
            Json::Value jChild;
            object->serialize(jChild);
            jValue["objects"].append(jChild);
        }
    }
    
    void GUIEnvironment::deserialize(const Json::Value& jValue)
    {
//        if (jValue["origin"] != Json::nullValue) {
//            m_origin.deserialize(jValue["origin"]);
//        }
//
//        if (jValue["size"] != Json::nullValue) {
//            m_size.deserialize(jValue["size"]);
//        }
//
//		Json::Value importData = jValue["import"];
//		if (importData != Json::nullValue) {
//			//Import files into this environment
//			for (auto it = importData.begin(); it != importData.end(); it++) {
//				std::string importFile = (*it).asString();
//				Json::Value importJson = Serializer::loadFile(getPath() + importFile);
//				if (importJson != Json::nullValue) {
//					deserialize(importJson);
//				}
//			}
//
//		}
//
        Json::Value renderData = jValue["renderData"];
        if (renderData != Json::nullValue) {
            for ( auto it = renderData.begin(); it != renderData.end() ; it++) {
                Json::Value renderObject = *it;
                std::string id = renderObject["id"].asString();
                m_renderData[id] = renderObject;
            }
        }
        
        for (auto jChild : jValue["objects"]) {
            std::shared_ptr<GUIObject> obj = GUIFactory::buildObject(jChild, shared_from_this());
            if (obj != nullptr) {
                m_objects.emplace_back(obj);
            }
        }
        
        m_bNeedsUpdate = true;
    }
    
    void GUIEnvironment::addObject(std::shared_ptr<GUIObject> newObject)
    {
        // object is null
        if (newObject.get() == nullptr) {
            return;
        }
        
        // object alreadt exists
        if (std::find(m_objects.begin(), m_objects.end(), newObject) != m_objects.end()) {
            return;
        }
        
        newObject->setGUIEnvironment(shared_from_this());
        m_objects.emplace_back(newObject);
        m_bNeedsUpdate = true;
    }
    
    void GUIEnvironment::draw() const
    {
        for (auto & object : m_objects) {
            if (object->isVisible()) {
                object->draw();
            }
        }
    }
    
    void GUIEnvironment::Tick(const Time & deltaTime)
    {
        //Order object
        //TODO Consider optimizing to only resort if children depth has changed
        if (m_bNeedsUpdate) {
            std::sort(m_objects.begin(), m_objects.end(), GUIObject::sortFunction );
        }
        
        for (auto & object : m_objects) {
            if (m_bNeedsUpdate) {
                object->setNeedsUpdate();
//                Recti setZone(m_origin.x, m_origin.y, m_size.x, m_size.y);
//                object->setWorldZone({m_origin, setZone});
            }
            
            if (object->isActive()) {
                object->Tick(deltaTime);
            }
        }
        
        m_bNeedsUpdate = false;
    }
    
    std::shared_ptr<GUIObject> GUIEnvironment::findObject(const std::string & objectID) const
    {
        std::shared_ptr<GUIObject> obj(nullptr);
        
        for (auto it = m_objects.begin(); nullptr == obj && it != m_objects.end(); ++it) {
            obj = ((*it)->ID().compare(objectID) == 0) ? (*it) : (*it)->findChild(objectID);
        }
        return obj;
    }
    
    std::shared_ptr<GUIObject> GUIEnvironment::findObjectAt(const glm::vec2 & point) const
    {
        if ((point.x < m_origin.x || point.x > (m_origin.x + m_size.x))
            || (point.y < m_origin.y || point.y > (m_origin.y + m_size.y))) {
            return nullptr;
        }
        for (auto & object : m_objects) {
			glm::vec2 offsetPoint = point - m_origin;
            if (object->isActive() && object->isVisible() && object->containsPoint(offsetPoint)) {
                return object->findObjectAt(offsetPoint);
            }
        }
        
        return nullptr;
    }
    
    Json::Value GUIEnvironment::getRenderData(const std::string & renderID)
    {
        auto findItr = m_renderData.find(renderID);
        return (findItr != m_renderData.end()) ? findItr->second : Json::nullValue;
    }
    
    const glm::vec2 & GUIEnvironment::getSize() const
    {
        return m_size;
    }
    
} //namespace citadel::gui
