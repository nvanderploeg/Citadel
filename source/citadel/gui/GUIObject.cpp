//
//  GUIObject.cpp
//
//
//  Created by Norman van der Ploeg on 2017-04-02.
//  Copyright © 2021 Nanzero interactive. All rights reserved.
//


#include <gui/GUIObject.hpp>

#include <system/serializer.h>

namespace citadel::gui {
    GUIObject::GUIObject(const std::string & ID)
		: m_ID(ID)
		, m_depth(0)
    {

	}

    bool GUIObject::sortFunction(std::shared_ptr<GUIObject> a, std::shared_ptr<GUIObject> b)
    {
        return a->m_depth < b->m_depth;
    }
    
    bool GUIObject::containsPoint(const glm::vec2 & point) const
    {
        
        if (point.x < m_position.x)
            return false;
        if (point.x > m_position.x + m_size.x)
            return false;
        if (point.y < m_position.y)
            return false;
        if (point.y > m_position.y + m_size.y )
            return false;
        return true;
    }
  
    void GUIObject::serialize(Json::Value& jValue) const
    {
        jValue["id"] = m_ID;
//		m_position.serialize(jValue["position"]);
        jValue["isActive"] = m_bIsActive;
        jValue["isVisible"] = m_bIsVisible;
        jValue["depth"] = m_depth;
//        m_position.serialize(jValue["position"]);
//        m_size.serialize(jValue["size"]);
        
        jValue["children"] = Json::arrayValue;
        //TODO add additional values!
        for (auto it = m_children.begin(); it != m_children.end(); ++it) {
            Json::Value jChild;
            (*it)->serialize(jChild);
            jValue["children"].append(jChild);
        }
    }

    void GUIObject::deserialize(const Json::Value& jValue)
    {
        m_ID = jValue["id"].asString();
//		m_position.deserialize(jValue["position"]);
//        m_size.deserialize(jValue["size"]);
        m_depth = jValue.get("depth", 0).asInt();
        m_bIsVisible = jValue.get("isVisible", true).asBool();
        m_bIsActive = jValue.get("isActive", true).asBool();
        
//        Json::Value renderData = jValue.get("renderData", Json::arrayValue);
//        for (auto data : renderData) {
//            std::string id = data.get("id", "").asString();
//            if (id != "") {
//                m_env->addRenderData(id, data);
//            }
//        }
        
//        for (auto jChild : jValue.get("children", Json::arrayValue)) {
//            addChild(GUIFactory::buildObject(jChild, m_env));
//        }
        
//        for (auto jChild : jValue.get("constraint", Json::arrayValue)) {
//            auto targetName = jChild.get("target", Json::stringValue);
//            auto targetHook = jChild.get("target_hook", Json::intValue);
//            auto sourceHook = jChild.get("source_hook", Json::intValue);
//
//            auto targetObj = m_env->findObject(targetName.asString());
//
//            if (targetObj) {
//                addConstraint({targetObj, (GUIConstraintHook)sourceHook.asInt(), (GUIConstraintHook)targetHook.asInt()});
//            }
//        }
        
//        for (auto jTrigger : jValue.get("triggers", Json::arrayValue)) {
//            auto trigger = std::make_unique<GUIActionTrigger>(shared_from_this());
//            trigger->deserialize(jTrigger);
//            std::string triggerName = trigger->getTrigger();
//
//            if (triggerName.length() > 1) {
//                m_triggers[triggerName] = std::move(trigger);
//            }
//        }
    }
    
    void GUIObject::draw() const
    {
        for (auto child : m_children) {
            if (child->m_bIsVisible) {
                child->draw();
            }
        }
    }

    void GUIObject::setWorldZone(const GUIZone& zone)
    {
        m_worldZone = zone;
        setNeedsUpdate();
    }

    GUIZone GUIObject::calculateSubWorld()
    {
        GUIZone subWorld = m_worldZone;
        subWorld.origin += m_position;
//        subWorld.zone.left = subWorld.origin.x;
//        subWorld.zone.top = subWorld.origin.y;
//        subWorld.zone.width = m_size.x;
//        subWorld.zone.height = m_size.y;
        
//
//        if (isCulling()) {
//            if (subWorld.zone.left < m_worldZone.zone.left) {
//                auto offset = m_worldZone.zone.left - subWorld.zone.left;
//                subWorld.zone.left = m_worldZone.zone.left;
//                subWorld.zone.width -= offset;
//            }
//
//            if (subWorld.zone.top < m_worldZone.zone.top) {
//                auto offset = m_worldZone.zone.top - subWorld.zone.top;
//                subWorld.zone.top = m_worldZone.zone.top;
//                subWorld.zone.height -= offset;
//            }
//
//            if (subWorld.zone.left + subWorld.zone.width > m_worldZone.zone.left + m_worldZone.zone.width ) {
//                subWorld.zone.width -= (subWorld.zone.left + subWorld.zone.width) - (m_worldZone.zone.left + m_worldZone.zone.width);
//
//            }
//            if (subWorld.zone.top + subWorld.zone.height > m_worldZone.zone.top + m_worldZone.zone.height ) {
//                subWorld.zone.height -= (subWorld.zone.top + subWorld.zone.height) - (m_worldZone.zone.top + m_worldZone.zone.height);
//
//            }
//        }
//        if (subWorld.zone.height < 0) {
//            subWorld.zone.height = 0;
//        }
//        if (subWorld.zone.width < 0) {
//            subWorld.zone.width = 0;
//        }
            
//        subWorld.zone.width = std::min(m_size.x, m_worldZone.zone.width - m_position.x);
//        subWorld.zone.height = std::min(m_size.y, m_worldZone.zone.height - m_position.y);
        return subWorld;
    }

    void GUIObject::Tick(const Time& deltaTime)
    {
        std::sort(m_children.begin(), m_children.end(), GUIObject::sortFunction );
        
        auto subZone = calculateSubWorld();
        
        for (auto child : m_children)
        {
            if (needsUpdate()) {
                child->setWorldZone(subZone);
            }
                
            if (child->isActive()) {
                child->Tick(deltaTime);
            }
        }
        
        m_bNeedsUpdate = false;
    }


    void GUIObject::addConstraint(const GUIConstraint& constraint)
    {
        m_constraints.emplace_back(constraint);
    }

    void GUIObject::removeConstraint(const GUIConstraint& constraint)
    {
        for (auto it = m_constraints.begin(); it != m_constraints.end(); ++it) {
            if ((*it) == constraint) {
                m_constraints.erase(it);
                setNeedsUpdate();
                return;
            }
        }
    }
    
    bool GUIObject::removeChild(const std::string & ID)
    {
        for (auto it = m_children.begin(); it != m_children.end(); ++it) {
            if ((*it)->ID() == ID) {
                (*it).reset();
                m_children.erase(it);
                setNeedsUpdate();
                return true;
            }
        }
        return false;
    }
    
    std::shared_ptr<GUIObject> GUIObject::findChild(const std::string & ID) const
    {
        std::shared_ptr<GUIObject> obj(nullptr);
        
        for (auto it : m_children) {
            obj = (it->m_ID.compare(ID) == 0) ? it : it->findChild(ID);
            if (obj) {
                break;
            }
        }
        return obj;
    }
    
    void GUIObject::addChild(std::shared_ptr<GUIObject> newChild)
    {
        if (nullptr == newChild) {
            return;
        }
        if (newChild.get() == this) {
            return;
        }
        if (std::find(m_children.begin(), m_children.end(), newChild) != m_children.end()) {
            return;
        }
        
        newChild->m_env = m_env;
        m_children.emplace_back(newChild);
        setNeedsUpdate();
    }
    
    void GUIObject::addChild(std::string file)
    {
        Json::Value jroot = Serializer::loadFile(file);
        addChild(jroot);
    }
    
    void GUIObject::addChild(Json::Value jValue)
    {
        if (jValue.isArray())  {
            for (auto it = jValue.begin(); it != jValue.end(); ++it)  {
//                addChild(GUIFactory::buildObject(*it, m_env));
            }
        }
        else {
//            addChild(GUIFactory::buildObject(jValue, m_env));
        }
    }
    
    std::shared_ptr<GUIObject> GUIObject::findObjectAt(const glm::vec2 & point)
    {
        std::shared_ptr<GUIObject> obj(nullptr);
        
        for (auto it = m_children.rbegin(); it != m_children.rend(); ++it) {
            obj = *it;
            glm::vec2 offsetPoint = point - m_position;
            if (obj->isActive() && obj->isVisible() && obj->containsPoint(offsetPoint)) {
                return obj->findObjectAt(point);
            }
        }
        
        return shared_from_this();
    }

    void GUIObject::onActionEvent(std::string eventName, std::shared_ptr<GUIObject> emitter)
    {
//        auto trigger = m_triggers.find(eventName);
//        if (trigger != m_triggers.end()) {
//            trigger->second->Trigger(emitter);
//        }
    }

} // namespace citadel::gui
