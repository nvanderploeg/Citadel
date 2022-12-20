#include "demoGame.h"

#include <iostream>
#include "demoScene.h"

void DemoGame::OnGameDidFinishInitialization(citadel::CitadelGame* pGame)
{
    std::cout << "didFinishInit start" << std::endl;

    auto sceneStack = pGame->GetSceneStack();
    auto scene = std::make_unique<DemoScene>(sceneStack);
    sceneStack->Push(std::move(scene));

    std::cout << "didFinishInit end" << std::endl;
}