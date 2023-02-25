//
//  GUIRenderObj.hpp

//
//  Created by Norman van der Ploeg on 2017-10-15.
//  Copyright © 2021 Nanzero. All rights reserved.
//

#pragma once
#include <memory>
#include <glm/glm.hpp> //For mat

#include <system/JSONSerializable.h>
#include <system/tickable.h>

namespace citadel::gui
{
    
    struct GUIBorderSize : public IJSONSerializable
    {
        float top, right, bottom, left;
        
        GUIBorderSize() : top(0.f), right(0.f), bottom(0.f), left(0.f) { }
        
        inline void serialize(Json::Value& jValue) const override
        {
            jValue["top"] = top;
            jValue["right"] = right;
            jValue["bottom"] = bottom;
            jValue["left"] = left;
        }
        
        inline void deserialize(const Json::Value& jValue) override
        {
            top = jValue.get("top", 0.0f).asFloat();
            right = jValue.get("right", 0.0f).asFloat();
            bottom = jValue.get("bottom", 0.0f).asFloat();
            left = jValue.get("left", 0.0f).asFloat();
        }
    };
    
    class GUIRenderObject : public ITickable, public IJSONSerializable
    {
    protected:
//        Texture * m_texture;
//        sf::VertexArray m_vertices;
        glm::vec4 m_textureRect;
        glm::vec4 m_bounds;
        GUIBorderSize m_borderSize;
        bool m_needsUpdate;
//        std::vector<Colour> m_vertexColours;
        
    public:
        GUIRenderObject() = default;
        virtual ~GUIRenderObject() = default;
        virtual void serialize(Json::Value& jValue) const override;
        virtual void deserialize(const Json::Value& jValue) override;
        
        virtual void draw() const;
        virtual void Tick(const Time & deltaTime) override;
        
//        Texture * getTexture() { return m_texture; }
        
        virtual void setPosition(const glm::vec2& position);
        virtual void setSize(const glm::vec2 size);
        virtual void setBounds(const glm::vec4& bounds);
        void setBorderSize(const GUIBorderSize & borderSize);
        void setBoundsAndBorderSize(const glm::vec4& bounds, const GUIBorderSize& borderSize);
        
//        void setFillColour(const Colour& colour);
//        void setVertexColours(const std::vector<Colour>& vertexColors);
//    private:
        void setTextureCoords(const glm::vec4& textureRect);
        void updateVertices();
        void syncVertexColours();
    };
    
} // namespace citadel::gui

