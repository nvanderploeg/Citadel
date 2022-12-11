#include "demoScene.h"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "citadelSystem.h"

#include "transformComponent.h"
#include "gameObject.h"

using namespace std;

namespace {
    const std::string VIKING_MODEL_PATH = "models/viking_room.obj";
}

DemoScene::DemoScene()
:Scene()
{
    pGameObject = std::make_shared<citadel::GameObject>();
    AddGameObject(pGameObject);
    auto obj1 = citadel::VulkanGraphics::Instance()->Load(VIKING_MODEL_PATH, "");
    auto obj2 = obj1;
    obj2.model = glm::translate(glm::mat4(1.0), glm::vec3(0,0,2));

    m_objects.emplace_back(obj1);
    m_objects.emplace_back(obj2);


        glm::vec3 pos;
        glm::vec3 color;
        glm::vec2 texCoord;
    citadel::RenderPayload obj3;
    const std::vector<citadel::Vertex> vertices = {
        {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
    };
    obj3.vertexBuffer = citadel::VulkanGraphics::Instance()->CreateVertexBuffer(vertices);

    const std::vector<uint32_t> indices = {
        0, 1, 2, 2, 3, 0
    };
    obj3.indexBuffer = citadel::VulkanGraphics::Instance()->CreateIndexBuffer(indices);
    obj3.indexCount = indices.size();

    obj3.model = glm::translate(glm::mat4(1.0), glm::vec3(0,0,-1));

    
    m_objects.emplace_back(obj3);
    std::cout << "DemoScene() finish" << std::endl;
}


void DemoScene::Tick(citadel::Time &deltaTime)
{
    std::cout << "Tick" << std::endl;
    citadel::Scene::Tick(deltaTime);

    auto transform = static_cast<citadel::TransformComponent*>(pGameObject->GetComponent("transform"));

    timer += deltaTime;
    if (timer.asSeconds() > 1)
        timer -= citadel::Time::seconds(1) ;

    auto angle = lerp((citadel::f32)0, (citadel::f32)1, timer.asSeconds()) * (citadel::f32)360;

    auto X = cos(angle) * 10;
    auto Y = sin(angle) * 10;

    if (transform)
    {
        transform->position.x = X;
        transform->position.y = Y;
    }
}

void DemoScene::Draw() const
{
    citadel::Scene::Draw();  
    auto transform = static_cast<citadel::TransformComponent*>(pGameObject->GetComponent("transform"));
    if (transform) {
        std::cout << "\"Drawing\" Object at " << transform->position.x << " , " << transform->position.y << std::endl; 
    }
    static auto startTime = std::chrono::high_resolution_clock::now();
    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

     std::cout << "Try to draw object!" << std::endl;
    for (auto& obj : m_objects) {

        std::cout << "Try to draw object!" << std::endl;
        citadel::VulkanGraphics::Instance()->AddToDraw(obj);
    }
}