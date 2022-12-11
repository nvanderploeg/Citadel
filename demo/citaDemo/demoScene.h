#include "citadel/citadel.h"
#include "citadel/game/scene.h"

class DemoScene : public citadel::Scene
{
public:
    DemoScene();

    void Tick(citadel::Time &deltaTime) override;
    void Draw(std::shared_ptr<citadel::VulkanGraphics> graphics) const override;

private:
    std::shared_ptr<citadel::GameObject> pGameObject;
    citadel::Time timer;
};