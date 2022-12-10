#include "citadel/citadel.h"
#include "citadel/game/scene.h"

class DemoScene : public citadel::Scene
{
public:
    DemoScene();

    void Tick(citadel::Time &deltaTime) override;
    void Draw() override;

private:
    citadel::ecs::EntityID entity;
    //TransformComponent* m_pTransform;
    //std::shared_ptr<citadel::GameObject> pGameObject;
    citadel::Time timer;
};