
#include "demoScene.h"

//#include <iostream>

//#include <glm/glm.hpp>
//#include <glm/gtc/quaternion.hpp>

#include "citadelSystem.h"
#include "citadelECS.h"
#include "citadel/input/inputRouter.h"

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
    float speed = 1.f;
    float topBound = 1.f;
    float bottomBound = -1.f;
    bool goingUp = true;

};

struct Rotate 
{
    float speed = 1.f;
};

struct PlayerInputComponent
{
    glm::vec3 inputRaw;
    bool isRunning;
    bool isGrounded;
};

DemoScene::DemoScene()
    :Scene()
{
    auto entity = registry.CreateEntity();
    auto transform = registry.AddComponent<TransformComponent>(entity);
    //auto rotate = registry.AddComponent<Rotate>(entity);
    //rotate->speed = 0.5;
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
    mesh3->texture = citadel::VulkanGraphics::Instance()->CreateTexture("textures/nan0.png");

    //auto player = registry.CreateEntity();
    //auto playerTransform = registry.AddComponent<TransformComponent>(player);
    auto playerInputComponent = registry.AddComponent<PlayerInputComponent>(entity);
    playerInputComponent->isGrounded = true;
    playerInputComponent->isRunning = false;

    std::cout << "DemoScene() finish" << std::endl;
}


void DemoScene::Tick(const citadel::Time &deltaTime)
{
    PlayerInputSystem(deltaTime);

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

        auto angle = lerp(0.0f, 6.28f, currentTime);

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

    for (citadel::ecs::EntityID entity : citadel::ecs::Filter<TransformComponent, PlayerInputComponent>(&registry))
    {
        auto transform = registry.GetComponent<TransformComponent>(entity);
        std::cout << "player (id: " << entity << ") position: {" << transform->position.x << ", " << transform->position.y << ", " << transform->position.z << "}\n";
    }
}

void DemoScene::BindInput(const std::shared_ptr<citadel::InputRouter>& inputRouter)
{
    // load the input mappings from a file defined in the gameConfig
    // TODO: non-literal filename and bindings?
    Json::Value jContext = citadel::Serializer::loadFile("config/inputContext.cfg");
    inputRouter->SetInputContext(jContext);

    inputRouter->BindCallbackToLabel("moveUp", [this](citadel::InputEventData data)
        {
            auto keyData = std::get<citadel::KeyEventData>(data);
            for (auto entity : citadel::ecs::Filter<TransformComponent, PlayerInputComponent>(&registry))
            {
                auto inputComponent = registry.GetComponent<PlayerInputComponent>(entity);
                if (inputComponent->isGrounded)
                    inputComponent->inputRaw.x += (keyData.action == 1 ? 1.0f : -1.0f);
            }
            return true;
        });
    inputRouter->BindCallbackToLabel("moveDown", [this](citadel::InputEventData data)
        {
            auto keyData = std::get<citadel::KeyEventData>(data);
            for (auto entity : citadel::ecs::Filter<TransformComponent, PlayerInputComponent>(&registry))
            {
                auto inputComponent = registry.GetComponent<PlayerInputComponent>(entity);
                if (inputComponent->isGrounded)
                    inputComponent->inputRaw.x += (keyData.action == 1 ? -1.0f : 1.0f);
            }
            return true;
        });
    inputRouter->BindCallbackToLabel("moveLeft", [this](citadel::InputEventData data)
        {
            auto keyData = std::get<citadel::KeyEventData>(data);
            for (auto entity : citadel::ecs::Filter<TransformComponent, PlayerInputComponent>(&registry))
            {
                auto inputComponent = registry.GetComponent<PlayerInputComponent>(entity);
                if (inputComponent->isGrounded)
                    inputComponent->inputRaw.y += (keyData.action == 1 ? -1.0f : 1.0f);
            }
            return true;
        });
    inputRouter->BindCallbackToLabel("moveRight", [this](citadel::InputEventData data)
        {
            auto keyData = std::get<citadel::KeyEventData>(data);
            for (auto entity : citadel::ecs::Filter<TransformComponent, PlayerInputComponent>(&registry))
            {
                auto inputComponent = registry.GetComponent<PlayerInputComponent>(entity);
                if (inputComponent->isGrounded)
                    inputComponent->inputRaw.y += (keyData.action == 1 ? 1.0f : -1.0f);
            }
            return true;
        });
    inputRouter->BindCallbackToLabel("runToggle", [this](citadel::InputEventData data)
        {
            for (auto entity : citadel::ecs::Filter<TransformComponent, PlayerInputComponent>(&registry))
            {
                auto inputComponent = registry.GetComponent<PlayerInputComponent>(entity);
                if (inputComponent->isGrounded)
                    inputComponent->isRunning = !inputComponent->isRunning;
            }
            return true;
        });


    // test binding for mouse click
    inputRouter->BindCallbackToLabel("mouseClick", [this](citadel::InputEventData data)
        {
            std::cout << "mouse button up\n";
            return true;
        });

    inputRouter->BindCallbackToLabel("mouseScroll", [this](citadel::InputEventData data) {
        auto& scrollData = std::get<citadel::MouseScrollEventData>(data);
        if (scrollData.yOffset != 0) {

            fieldOfView += (scrollData.yOffset > 0) ? 5 : -5;
            fieldOfView = std::max(45.f, fieldOfView);
            fieldOfView = std::min(120.f, fieldOfView);
            citadel::VulkanGraphics::Instance()->SetFoV(fieldOfView);
            return true;
        }
        return false;
        });
}

void DemoScene::FreeInput(const std::shared_ptr<citadel::InputRouter>& inputRouter)
{
    // TODO: we should probably unbind things
}

void DemoScene::PlayerInputSystem(const citadel::Time& deltaTime)
{
    for (citadel::ecs::EntityID entity : citadel::ecs::Filter<TransformComponent, PlayerInputComponent>(&registry))
    {
        auto inputComponent = registry.GetComponent<PlayerInputComponent>(entity);
        glm::vec3 moveDirection = inputComponent->inputRaw * deltaTime.asSeconds();

        auto transform = registry.GetComponent<TransformComponent>(entity);
        transform->position += moveDirection;
    }
}
