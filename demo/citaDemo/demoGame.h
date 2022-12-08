#include "citadel/citadel.h"


class DemoGame: public citadel::CitadelGameDelegate
{
public:
    DemoGame() = default;
    ~DemoGame() = default;
    void OnGameDidFinishInitialization(citadel::CitadelGame* game) override;
};