#include "demoScene.h"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "citadelSystem.h"
#include "citadelECS.h"

#include "transformComponent.h"

using namespace std;

namespace {
    const std::string VIKING_MODEL_PATH = "models/viking_room.obj";
    const std::vector<citadel::Vertex> vertices = {
        {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
    };

    const std::vector<uint32_t> indices = {
        0, 1, 2, 2, 3, 0
    };

}

struct Bounce 
{
    float speed = 3;
    float topBound = 0.5;
    float bottomBound = -2;
    bool goingUp = true;

};

struct Rotate 
{
    int speed = 1;
};

DemoScene::DemoScene()
    :Scene()
{
    auto entity = registry.CreateEntity();
    auto transform = registry.AddComponent<TransformComponent>(entity);
    auto rotate = registry.AddComponent<Rotate>(entity);
    rotate->speed = 2;
    auto mesh = registry.AddComponent<citadel::MeshData>(entity);
    *mesh = citadel::VulkanGraphics::Instance()->Load(VIKING_MODEL_PATH, "");

    auto entity2 = registry.CreateEntity();
    auto transform2 = registry.AddComponent<TransformComponent>(entity2);
    auto mesh2 = registry.AddComponent<citadel::MeshData>(entity2);
    registry.AddComponent<Rotate>(entity2);
    auto bounce = registry.AddComponent<Bounce>(entity2);
    bounce->topBound = 2.0;
    bounce->bottomBound = 1.0;
    *mesh2 = *mesh;
    transform2->position.z += 1.5;

    auto entity3 = registry.CreateEntity();
    auto transform3 = registry.AddComponent<TransformComponent>(entity3);
    auto mesh3 = registry.AddComponent<citadel::MeshData>(entity3);
    registry.AddComponent<Bounce>(entity3);

    transform3->position.z -= 1.5;

    mesh3->vertexBuffer = citadel::VulkanGraphics::Instance()->CreateVertexBuffer(vertices);

    mesh3->indexBuffer = citadel::VulkanGraphics::Instance()->CreateIndexBuffer(indices);
    mesh3->indexCount = indices.size();

    std::cout << "DemoScene() finish" << std::endl;
}


void DemoScene::Tick(const citadel::Time &deltaTime)
{
    timer += deltaTime;

    for (citadel::ecs::EntityID entity : citadel::ecs::Filter<TransformComponent, Bounce>(&registry)) 
    {
        auto transform = registry.GetComponent<TransformComponent>(entity);
        auto bounce = registry.GetComponent<Bounce>(entity);

        transform->position.z += bounce->speed * deltaTime.asSeconds() * (bounce->goingUp ? 1.0 : -1.0);

        if ((transform->position.z >= bounce->topBound && bounce->goingUp)
            || (transform->position.z <= bounce->bottomBound && !bounce->goingUp)) 
        {
            bounce->goingUp = !bounce->goingUp;
        }
    }

    for (citadel::ecs::EntityID entity : citadel::ecs::Filter<TransformComponent, Rotate>(&registry))
    {
        auto transform = registry.GetComponent<TransformComponent>(entity);
        auto rotate = registry.GetComponent<Rotate>(entity);

        if (transform == nullptr)
            continue;
        
        auto currentTime = timer.asSeconds() * rotate->speed;
        currentTime -= (int)currentTime;

        auto angle = lerp(0.0, 6.28, currentTime);

        auto X = cos(angle);
        auto Y = sin(angle);

        transform->position.x = X;
        transform->position.y = Y;
    }
}

void DemoScene::Draw()
{
    for (citadel::ecs::EntityID entity : citadel::ecs::Filter<TransformComponent, citadel::MeshData>(&registry))
    {
        auto transform = registry.GetComponent<TransformComponent>(entity);
        auto mesh = registry.GetComponent<citadel::MeshData>(entity);
        
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), 0 * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::translate(model, transform->position);

        citadel::RenderPayload payload({model, *mesh});

        citadel::VulkanGraphics::Instance()->AddToDraw(payload);
    }
 
}