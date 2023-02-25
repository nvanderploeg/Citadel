//
//  GUIRenderObj.cpp

//
//  Created by Norman van der Ploeg on 2017-10-15.
//  Copyright © 2021 Nanzero. All rights reserved.
//


#include <gui/GUIRenderObject.hpp>



namespace citadel::gui {
    

    void GUIRenderObject::serialize(Json::Value& jValue) const
    {
        // TODO: serialize all the things
    }

    void GUIRenderObject::deserialize(const Json::Value& jValue)
    {
        // NOTE: parse colour before we parse the texture so that colour can be applied to the texture
        
//        Json::Value jColour = jValue.get("colour", Json::nullValue);
//        if (jColour != Json::nullValue)
//        {
//            Json::Value jFill = jColour.get("fill", Json::nullValue);
//            if (jFill != Json::nullValue)
//            {
//                Colour fillColour;
//                fillColour.deserialize(jFill);
//                setFillColour(fillColour);
//            }
//
//            Json::Value jVertexColours = jColour.get("vertex", Json::nullValue);
//            if (jVertexColours != Json::nullValue)
//            {
//                Colour vertexColour;
//                std::vector<Colour> vertexColours;
//                for (auto & jColour : jVertexColours)
//                {
//                    vertexColour.deserialize(jColour);
//                    vertexColours.emplace_back(vertexColour);
//                }
//                setVertexColours(vertexColours);
//            }
//        }
//
//        //TODO: vertex colour data needs to sync with rect data!!!
//        // NOTE: by default, we'll have one quad. If any are specified in data, this one will be overwritten.
//        m_vertices.clear();
//        m_vertices.resize(4);
//
//        Json::Value jTexture = jValue.get("texture", Json::nullValue);
//        if (jTexture != Json::nullValue)
//        {
//            Json::Value jName = jTexture.get("name", Json::nullValue);
//            if (jName != Json::nullValue)
//            {
//                auto & textureManager = Game::get()->getTextureManager();
//                // NOTE: TextureManager checks for nullptr; releasing any existing texture
//                textureManager.releaseResource(m_texture);
//                m_texture = textureManager.getResource(jName.asString());
//                if (jTexture["rect"] != Json::nullValue ) {
//                    Rectf textureRect;
//                    textureRect.deserialize(jTexture["rect"]);
//                    setTextureCoords(textureRect);
//                }
//                else {
//                    setTextureCoords({0.0f, 0.0f, m_texture->getSize().x, m_texture->getSize().y});
//                }
//            }
//        }
        
        syncVertexColours();
        
        m_needsUpdate = true;
    }

    void GUIRenderObject::syncVertexColours()
    {
//        if (m_vertices.getVertexCount() == m_vertexColours.size())
//        {
//            for (auto i = 0; i < m_vertexColours.size(); ++i)
//            {
//                m_vertices[i].color = sf::Color(m_vertexColours[i].toInteger());
//            }
//        }
    }

//    void GUIRenderObject::setFillColour(const Colour& colour) {
////        m_vertexColours.resize(0);
////        m_vertexColours.resize(4, colour);
//        syncVertexColours();
//    }
//
//    void GUIRenderObject::setVertexColours(const std::vector<Colour>& vertexColours)
//    {
////        m_vertexColours = vertexColours;
//    }

    void GUIRenderObject::setPosition(const glm::vec2& position)
    {
//        m_bounds.setPosition(position);
        m_needsUpdate = true;
    }
    
    void GUIRenderObject::setSize(const glm::vec2 size)
    {
//        m_bounds.setSize(size);
        m_needsUpdate = true;
    }
    
    void GUIRenderObject::setBounds(const glm::vec4& bounds)
    {
        m_bounds = bounds;
        m_needsUpdate = true;
    }
    
    void GUIRenderObject::setBorderSize(const GUIBorderSize& borderSize)
    {
        m_borderSize = borderSize;
        m_needsUpdate = true;
    }
    
    void GUIRenderObject::setBoundsAndBorderSize(const glm::vec4& bounds, const GUIBorderSize& borderSize)
    {
        m_bounds = bounds;
        m_borderSize = borderSize;
        m_needsUpdate = true;
    }
    
    void GUIRenderObject::draw() const
    {
    }

    void GUIRenderObject::Tick(const Time& deltaTime)
    {
        if (m_needsUpdate)
        {
            updateVertices();
            m_needsUpdate = false;
        }
    }
    
    void GUIRenderObject::setTextureCoords(const glm::vec4& textureRect) {
        m_textureRect = textureRect;
    }
    void GUIRenderObject::updateVertices()
    {
//        m_vertices[0].position = { m_bounds.left, m_bounds.top + m_bounds.height };
//        m_vertices[1].position = { m_bounds.left, m_bounds.top };
//        m_vertices[2].position = { m_bounds.left + m_bounds.width, m_bounds.top };
//        m_vertices[3].position = { m_bounds.left + m_bounds.width, m_bounds.top + m_bounds.height };
//
//        if (m_texture)
//        {
//            m_vertices[0].texCoords = { m_textureRect.left, m_textureRect.top + m_textureRect.height };
//            m_vertices[1].texCoords = { m_textureRect.left, m_textureRect.top };
//            m_vertices[2].texCoords = { m_textureRect.left + m_textureRect.width, m_textureRect.top };
//            m_vertices[3].texCoords = { m_textureRect.left + m_textureRect.width, m_textureRect.top + m_textureRect.height };
//        }
    }

} //namespace citadel::gui
