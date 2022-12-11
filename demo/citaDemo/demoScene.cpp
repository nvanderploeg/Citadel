#include "demoScene.h"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "citadelSystem.h"

#include "transformComponent.h"
#include "gameObject.h"

using namespace std;

DemoScene::DemoScene()
:Scene()
{
    pGameObject = std::make_shared<citadel::GameObject>();
    AddGameObject(pGameObject);
}


void DemoScene::Tick(citadel::Time &deltaTime)
{
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

    citadel::RenderPayload payload;

    payload.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    citadel::VulkanGraphics::Instance()->AddToDraw(payload);

    payload.model = glm::translate(glm::mat4(1.0f), glm::vec3(1,0,0));
    payload.model = glm::rotate(payload.model, time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    citadel::VulkanGraphics::Instance()->AddToDraw(payload);
}