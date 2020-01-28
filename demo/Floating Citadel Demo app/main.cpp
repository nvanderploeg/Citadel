//
//  main.cpp
//  Floating Citadel Demo app
//
//  Created by Norman van der Ploeg on 2020-01-17.
//  Copyright © 2020 Floating Citadel Games. All rights reserved.
//

#include "citadel/citadel.h"

using namespace citadel;

int main(int argc, const char * argv[]) {
    //Automatically looks for game.config and builds from there
    //You can instead pass in a path to the main game config file
    // or pass in a GameBuilder Object
    CitadelGame game;

    //Run the game
    return game.run();
}
