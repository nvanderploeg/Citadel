
#include "citadel/game/scene.h"

class DemoScene : public citadel::Scene
{
public:
    DemoScene();

    void Tick(const citadel::Time& deltaTime) override;
    void Draw() override;

    void BindInput(const std::shared_ptr<citadel::InputRouter>& inputRouter) override;
    void FreeInput(const std::shared_ptr<citadel::InputRouter>& inputRouter) override;
    
    void OnEnter() override;
    void OnExit() override;


private:
    citadel::Time timer;

    float fieldOfView = 90.f;

    void PlayerInputSystem(const citadel::Time& deltaTime);

};