#include "citadel/game/scene.h"

class DemoScene : public citadel::Scene
{
public:
    DemoScene();

    void Tick(const citadel::Time& deltaTime);
    void Draw() override;

private:
    citadel::ecs::EntityID m_entity;
    citadel::Time timer;
};