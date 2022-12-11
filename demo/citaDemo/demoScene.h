#include "citadel/game/scene.h"

class DemoScene : public citadel::Scene
{
public:
    DemoScene();

    void Tick(const citadel::Time& deltaTime);
    void Draw() override;

private:
    citadel::Time timer;

    std::vector<citadel::RenderPayload> m_objects;
};