
#include "citadel/game/scene.h"
#include "citadel/system/timer.h"

class DemoScene : public citadel::Scene
{
public:
    DemoScene(const std::shared_ptr<citadel::SceneStack>& sceneStack);

    void Tick(const citadel::Time& deltaTime) override;
    void Draw() override;

    void BindInput(const std::shared_ptr<citadel::InputRouter>& inputRouter) override;
    void FreeInput(const std::shared_ptr<citadel::InputRouter>& inputRouter) override;

private:
    citadel::Timer timer;
    citadel::Time rotateTimer;

    float fieldOfView = 90.f;

    void PlayerInputSystem(const citadel::Time& deltaTime);

};