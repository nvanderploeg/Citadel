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
//lib includes
#include "GLFW/glfw3.h"
//Citadel includes
#include "citadelGame.h"
#include "gameConfig.h"


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
    GLFWwindow* window = glfwCreateWindow(gameConfig->width, gameConfig->height, gameConfig->title.c_str(), NULL, NULL);
    if (!window) {
        return 501; // couldn't create window
    }

    // Keep running until term
    while (!glfwWindowShouldClose(window))
    {
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

} //namespace citadel
