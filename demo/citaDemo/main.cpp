//
//  main.cpp
//  Floating Citadel Demo app
//
//  Created by Norman van der Ploeg on 2020-01-17.
//  Copyright © 2020 Floating Citadel Games. All rights reserved.
//

#include "citadel/citadel.h"

#include "demoGame.h"

using namespace citadel;

int main(int argc, const char * argv[]) {
    //Automatically looks for game.config and builds from there
    //You can instead pass in a path to the main game config file
    //
    auto demo = std::make_shared<DemoGame>();
    CitadelGame game("", demo);

    //Run the game
    return game.run();
}


//getResourcePath is meant to help in crossplatform and sandbox situations
//For example on iOS, files are in a sandbox and need help to be found
//This main not be true of all platforms
std::string getResourcePath(void) {
    return "";
}