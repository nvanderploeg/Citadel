//
//  CitadelGame.cpp
//  CitadelEngine
//
//  Created by Norman van der Ploeg on 2020-01-17.
//  Copyright © 2020 Floating Citadel Games. All rights reserved.
//

//std includes
#include <stdlib.h>
#include <memory.h>
#include <iostream>
#include <unistd.h>

//lib includes
#include "GLFW/glfw3.h"

//Citadel includes
#include "citadelSystem.h"
#include "citadelGame.h"
#include "gameConfig.h"
#include "windowProperties.h"


using namespace std;
namespace citadel {

CitadelGame::CitadelGame() {
    ready = false;
    gameConfig = make_shared<GameConfig>("game.config");
    if (!glfwInit()) {
        // Initialization failed
        cout << "Failed to init glfw" << endl;
    }
    else {
        ready = true;
    }
}

int CitadelGame::run() {
    if (!ready) {
        return 500; //Failed to init
    }
    GLFWwindow* window = glfwCreateWindow(gameConfig->windowProperties->width, gameConfig->windowProperties->height, gameConfig->windowProperties->title.c_str(), NULL, NULL);
    if (!window) {
        return 501; // couldn't create window
    }
    
    glfwSetKeyCallback(window, [](GLFWwindow* window,int key, int scancode, int action, int mods){
        cout << "Key Callback" << endl << key << "," << scancode << "," << action << "," << mods << endl;
    });

    // Keep running until term
    static  Time frameTime = Time::seconds(1.f/60.f);
    Time frameTimer = Time::getCurrentTime();
    clock.restart();
    while (!glfwWindowShouldClose(window))
    {
        //Do Tick(Update objects)
        auto delta = clock.restart();
        
        if(delta.asSeconds() > 0.1) { // Just too long, lets reset
            delta = clock.restart();
        }
        Tick(delta);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        
        auto fTime = clock.getElapsedTime();
        if(fTime < frameTime) {
            usleep((frameTime - fTime).asMicroseconds());
        }
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}


void CitadelGame::Tick(Time &deltaTime) {
    std::cout << deltaTime.asSeconds() << std::endl;
}

} //namespace citadel
