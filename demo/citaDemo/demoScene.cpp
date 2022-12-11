#include "demoScene.h"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "citadelSystem.h"
#include "citadelECS.h"

#include "transformComponent.h"

using namespace std;

DemoScene::DemoScene()
    :Scene()
{
    auto entity = registry.CreateEntity();
    auto transform = registry.AddComponent<TransformComponent>(entity);
}


void DemoScene::Tick(const citadel::Time &deltaTime)
{
    for (citadel::ecs::EntityID entity : citadel::ecs::Filter<TransformComponent>(&registry))
    {
        TransformComponent* transform = registry.GetComponent<TransformComponent>(entity);

        if (transform == nullptr)
            continue;

        timer += deltaTime;
        if (timer.asSeconds() > 1)
            timer -= citadel::Time::seconds(1);

        auto angle = lerp((citadel::f32)0, (citadel::f32)1, timer.asSeconds()) * (citadel::f32)360;

        auto X = cos(angle) * 10;
        auto Y = sin(angle) * 10;

        transform->position.x = X;
        transform->position.y = Y;
    }
}

void DemoScene::Draw()
{
    for (citadel::ecs::EntityID entity : citadel::ecs::Filter<TransformComponent>(&registry))
    {
        TransformComponent* transform = registry.GetComponent<TransformComponent>(entity);

        if (transform == nullptr)
            continue;

        std::cout << "\"Drawing\" Object at " << transform->position.x << " , " << transform->position.y << std::endl;
    }
}