
#include "demoScene.h"
#include "camera.h"
#include "citadel.h"

#include "transformComponent.h"

using namespace std;

namespace {
    const std::string VIKING_MODEL_PATH = "models/viking_room.obj";
    const std::string VIKING_TEXTURE_PATH = "textures/viking_room.png";
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

DemoScene::DemoScene(const std::shared_ptr<citadel::SceneStack>& sceneStack)
    : Scene(sceneStack)
{
    m_renderer = std::make_shared<citadel::Renderer>(citadel::GraphicsCore::Instance());
    auto entity = m_registry->CreateEntity();
    auto transform = m_registry->AddComponent<TransformComponent>(entity);
    //auto rotate = registry.AddComponent<Rotate>(entity);
    //rotate->speed = 0.5;
    auto mesh = m_registry->AddComponent<citadel::MeshData>(entity);
    *mesh = citadel::GraphicsCore::Instance()->Load(VIKING_MODEL_PATH, VIKING_TEXTURE_PATH);
    auto camera = m_registry->AddComponent<citadel::Camera>(entity);

    auto entity2 = m_registry->CreateEntity();
    auto transform2 = m_registry->AddComponent<TransformComponent>(entity2);
    auto mesh2 = m_registry->AddComponent<citadel::MeshData>(entity2);
    m_registry->AddComponent<Rotate>(entity2);
    auto bounce = m_registry->AddComponent<Bounce>(entity2);
    bounce->topBound = 2.0;
    bounce->bottomBound = 1.0;
    *mesh2 = *mesh;
    transform2->position.z += 1.5;

    auto entity3 = m_registry->CreateEntity();
    auto transform3 = m_registry->AddComponent<TransformComponent>(entity3);
    auto mesh3 = m_registry->AddComponent<citadel::MeshData>(entity3);
    m_registry->AddComponent<Bounce>(entity3);
    transform3->position.z -= 1.5;
    mesh3->vertexBuffer = citadel::GraphicsCore::Instance()->CreateVertexBuffer(vertices);
    mesh3->indexBuffer = citadel::GraphicsCore::Instance()->CreateIndexBuffer(indices);
    mesh3->indexCount = indices.size();
    mesh3->texture = citadel::GraphicsCore::Instance()->CreateTexture("textures/nan0.png");

    //auto player = registry.CreateEntity();
    //auto playerTransform = registry.AddComponent<TransformComponent>(player);
    auto playerInputComponent = m_registry->AddComponent<PlayerInputComponent>(entity);
    playerInputComponent->isGrounded = true;
    playerInputComponent->isRunning = false;

    timer.Every(3, []() {std::cout << "every 3 seconds\n"; }).start();

    std::cout << "DemoScene() finish" << std::endl;
}


void DemoScene::Tick(const citadel::Time &deltaTime)
{
    timer.Tick(deltaTime);
    PlayerInputSystem(deltaTime);

    auto playerID = *(citadel::ecs::Filter<TransformComponent, PlayerInputComponent>(m_registry.get()).begin());
    auto cameraID = *(citadel::ecs::Filter<TransformComponent, citadel::Camera>(m_registry.get()).begin());

    auto camera = m_registry->GetComponent<citadel::Camera>(cameraID);
    auto playerTransform = m_registry->GetComponent<TransformComponent>(playerID);

    camera->m_position = playerTransform->position + glm::vec3(5, 5, 10);
    camera->m_target = playerTransform->position;

    rotateTimer += deltaTime;

    for (citadel::ecs::EntityID entity : citadel::ecs::Filter<TransformComponent, Bounce>(m_registry.get()))
    {
        auto transform = m_registry->GetComponent<TransformComponent>(entity);
        auto bounce = m_registry->GetComponent<Bounce>(entity);

        transform->position.z += bounce->speed * deltaTime.asSeconds() * (bounce->goingUp ? 1.0 : -1.0);

        if ((transform->position.z >= bounce->topBound && bounce->goingUp)
            || (transform->position.z <= bounce->bottomBound && !bounce->goingUp)) 
        {
            bounce->goingUp = !bounce->goingUp;
        }
    }

    for (citadel::ecs::EntityID entity : citadel::ecs::Filter<TransformComponent, Rotate>(m_registry.get()))
    {
        auto transform = m_registry->GetComponent<TransformComponent>(entity);
        auto rotate = m_registry->GetComponent<Rotate>(entity);

        if (transform == nullptr)
            continue;
        
        auto currentTime = rotateTimer.asSeconds() * rotate->speed;
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
    auto cameraID = *(citadel::ecs::Filter<TransformComponent, citadel::Camera>(m_registry.get()).begin());
    auto camera = m_registry->GetComponent<citadel::Camera>(cameraID);

    m_renderer->SetViewMatrix(camera->GetViewMatrix());

    m_renderer->Prepare();

        for (citadel::ecs::EntityID entity : citadel::ecs::Filter<TransformComponent, citadel::MeshData>(m_registry.get()))
        {
            auto transform = m_registry->GetComponent<TransformComponent>(entity);
            auto mesh = m_registry->GetComponent<citadel::MeshData>(entity);
            
            glm::mat4 model = glm::rotate(glm::mat4(1.0f), 0 * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::translate(model, transform->position);

            // std::cout << "drawing entity " << entity << std::endl;
            citadel::RenderPayload payload({model, *mesh});

            m_renderer->Add(payload);
        }

        for (citadel::ecs::EntityID entity : citadel::ecs::Filter<TransformComponent, PlayerInputComponent>(m_registry.get()))
        {
            auto transform = m_registry->GetComponent<TransformComponent>(entity);
            // std::cout << "player (id: " << entity << ") position: {" << transform->position.x << ", " << transform->position.y << ", " << transform->position.z << "}\n";
        }
    
    m_renderer->Submit();
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
            for (auto entity : citadel::ecs::Filter<TransformComponent, PlayerInputComponent>(m_registry.get()))
            {
                auto inputComponent = m_registry->GetComponent<PlayerInputComponent>(entity);
                if (inputComponent->isGrounded)
                    inputComponent->inputRaw.x += (keyData.action == 1 ? 1.0f : -1.0f);
            }
            return true;
        });
    inputRouter->BindCallbackToLabel("moveDown", [this](citadel::InputEventData data)
        {
            auto keyData = std::get<citadel::KeyEventData>(data);
            for (auto entity : citadel::ecs::Filter<TransformComponent, PlayerInputComponent>(m_registry.get()))
            {
                auto inputComponent = m_registry->GetComponent<PlayerInputComponent>(entity);
                if (inputComponent->isGrounded)
                    inputComponent->inputRaw.x += (keyData.action == 1 ? -1.0f : 1.0f);
            }
            return true;
        });
    inputRouter->BindCallbackToLabel("moveLeft", [this](citadel::InputEventData data)
        {
            auto keyData = std::get<citadel::KeyEventData>(data);
            for (auto entity : citadel::ecs::Filter<TransformComponent, PlayerInputComponent>(m_registry.get()))
            {
                auto inputComponent = m_registry->GetComponent<PlayerInputComponent>(entity);
                if (inputComponent->isGrounded)
                    inputComponent->inputRaw.y += (keyData.action == 1 ? -1.0f : 1.0f);
            }
            return true;
        });
    inputRouter->BindCallbackToLabel("moveRight", [this](citadel::InputEventData data)
        {
            auto keyData = std::get<citadel::KeyEventData>(data);
            for (auto entity : citadel::ecs::Filter<TransformComponent, PlayerInputComponent>(m_registry.get()))
            {
                auto inputComponent = m_registry->GetComponent<PlayerInputComponent>(entity);
                if (inputComponent->isGrounded)
                    inputComponent->inputRaw.y += (keyData.action == 1 ? 1.0f : -1.0f);
            }
            return true;
        });
    inputRouter->BindCallbackToLabel("runToggle", [this](citadel::InputEventData data)
        {
            for (auto entity : citadel::ecs::Filter<TransformComponent, PlayerInputComponent>(m_registry.get()))
            {
                auto inputComponent = m_registry->GetComponent<PlayerInputComponent>(entity);
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
            m_renderer->SetFoV(fieldOfView);
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
    for (citadel::ecs::EntityID entity : citadel::ecs::Filter<TransformComponent, PlayerInputComponent>(m_registry.get()))
    {
        auto inputComponent = m_registry->GetComponent<PlayerInputComponent>(entity);
        glm::vec3 moveDirection = inputComponent->inputRaw * deltaTime.asSeconds() * 10.f;

        auto transform = m_registry->GetComponent<TransformComponent>(entity);
        transform->position += moveDirection;
    }
}

