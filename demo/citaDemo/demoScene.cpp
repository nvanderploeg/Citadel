#include "demoScene.h"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "citadelSystem.h"

#include "transformComponent.h"
#include "gameObject.h"

using namespace std;

DemoScene::DemoScene()
//:Scene()
{
    //pGameObject = std::make_shared<citadel::GameObject>();
    //AddGameObject(pGameObject);
}


//void DemoScene::Tick(citadel::Time &deltaTime)
//{
    //citadel::Scene::Tick(deltaTime);

    //auto transform = static_cast<citadel::TransformComponent*>(pGameObject->GetComponent("transform"));

    //timer += deltaTime;
    //if (timer.asSeconds() > 1)
    //    timer -= citadel::Time::seconds(1) ;

    //auto angle = lerp((citadel::f32)0, (citadel::f32)1, timer.asSeconds()) * (citadel::f32)360;

    //auto X = cos(angle) * 10;
    //auto Y = sin(angle) * 10;

    //if (transform)
    //{
    //    transform->position.x = X;
    //    transform->position.y = Y;
    //}
//}

//void DemoScene::Draw() const
//{
    //citadel::Scene::Draw();  
    //auto transform = static_cast<citadel::TransformComponent*>(pGameObject->GetComponent("transform"));
    //if (transform) {
    //    std::cout << "\"Drawing\" Object at " << transform->position.x << " , " << transform->position.y << std::endl; 
    //}
//}