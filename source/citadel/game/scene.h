#pragma once

#include <vector>
#include <memory>
#include <string>

#include "cTime.h"

namespace citadel 
{
    class GameObject;
    class System;

    class Scene
    {
    protected:
        std::vector<std::shared_ptr<GameObject>> m_gameObjects;
        std::vector<std::shared_ptr<System>> m_systems;

    public:
        Scene() = default;
        virtual ~Scene() = default;

        void Load(std::string path);

        void AddGameObject(const std::shared_ptr<GameObject>& gameObject);
        void RemoveGameObject(const std::shared_ptr<GameObject>& gameObject);
        void AddSystem(const std::shared_ptr<System>& system);
        void RemoveSystem(const std::shared_ptr<System>& system);

        virtual void Tick(Time &deltaTime);
        virtual void Draw() const;
    };

}