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

DemoScene::DemoScene()
    :Scene()
{

    auto entity = registry.CreateEntity();
    auto transform = registry.AddComponent<TransformComponent>(entity);
    auto mesh = registry.AddComponent<citadel::MeshData>(entity);
    *mesh = citadel::VulkanGraphics::Instance()->Load(VIKING_MODEL_PATH, "");

    // auto entity2 = registry.CreateEntity();
    // auto transform2 = registry.AddComponent<TransformComponent>(entity2);
    // auto mesh2 = registry.AddComponent<citadel::MeshData>(entity2);
    // *mesh2 = *mesh;

    // auto entity3 = registry.CreateEntity();
    // auto transform3 = registry.AddComponent<TransformComponent>(entity3);
    // auto mesh3 = registry.AddComponent<citadel::MeshData>(entity3);

    // mesh3->vertexBuffer = citadel::VulkanGraphics::Instance()->CreateVertexBuffer(vertices);

    // mesh3->indexBuffer = citadel::VulkanGraphics::Instance()->CreateIndexBuffer(indices);
    // mesh3->indexCount = indices.size();

    std::cout << "DemoScene() finish" << std::endl;
}


void DemoScene::Tick(const citadel::Time &deltaTime)
{
    for (citadel::ecs::EntityID entity : citadel::ecs::Filter<TransformComponent>(&registry))
    {

        std::cout << "update transform for entity" << std::endl;
        TransformComponent* transform = registry.GetComponent<TransformComponent>(entity);

        if (transform == nullptr)
            continue;

        timer += deltaTime;
        if (timer.asSeconds() > 1)
            timer -= citadel::Time::seconds(1);

        auto angle = lerp((citadel::f32)0, (citadel::f32)1, timer.asSeconds()) * (citadel::f32)360;

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

        std::cout << "Drawing entity" << std::endl;
        auto transform = registry.GetComponent<TransformComponent>(entity);
        auto mesh = registry.GetComponent<citadel::MeshData>(entity);


        std::cout << "Drawing entity " <<  transform << " " << mesh << std::endl;
        
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), 0 * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::translate(model, transform->position);

        citadel::RenderPayload payload({model, *mesh});

        citadel::VulkanGraphics::Instance()->AddToDraw(payload);
    }
 
}