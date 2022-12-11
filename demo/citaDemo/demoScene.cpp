#include "demoScene.h"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "citadelSystem.h"

//#include "ecs/sceneView.h"
#include "ecs/transformComponent.h"
#include "gameObject.h"

using namespace std;

DemoScene::DemoScene()
//:Scene()
{
    entity = CreateEntity();
    auto transform = AddComponent<TransformComponent>(entity);
    //pGameObject = std::make_shared<citadel::GameObject>();
    //AddGameObject(pGameObject);
}


void DemoScene::Tick(citadel::Time &deltaTime)
{
    //citadel::Scene::Tick(deltaTime);

    //auto transform = static_cast<citadel::TransformComponent*>(pGameObject->GetComponent("transform"));
    
    
    //auto transform = GetComponent<TransformComponent>(entity);

    // NOTE: don't use SceneView, it's not working atm. also, there's a circular dependancy.
    //for (citadel::ecs::EntityID entity : citadel::ecs::SceneView<TransformComponent>(this))
    {
        TransformComponent* transform = GetComponent<TransformComponent>(entity);

        //if (transform == nullptr)
            //continue;

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
    //citadel::Scene::Draw();  
    //auto transform = static_cast<citadel::TransformComponent*>(pGameObject->GetComponent("transform"));
    TransformComponent * transform = GetComponent<TransformComponent>(entity);
    if (transform) {
        std::cout << "\"Drawing\" Object at " << transform->position.x << " , " << transform->position.y << std::endl; 
    }
}