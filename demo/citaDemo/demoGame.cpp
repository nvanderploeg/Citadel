#include "demoGame.h"

#include <iostream>
#include "demoScene.h"

void DemoGame::OnGameDidFinishInitialization(citadel::CitadelGame* game)
{
    std::cout << "didFinishInit start" << std::endl;
    auto scene = std::make_shared<DemoScene>();
    game->SetScene(scene);

    std::cout << "didFinishInit end" << std::endl;
}