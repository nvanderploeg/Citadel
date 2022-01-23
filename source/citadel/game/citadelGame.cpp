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

void initGL(int width, int height) {
    

    //Set the viewport
//    glViewport( 0.f, 0.f, width, height );

//    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0.0, width, height, 0.0, 1.0, -1.0 );

    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );
}

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
    
    glfwMakeContextCurrent(window);
    initGL(gameConfig->windowProperties->width, gameConfig->windowProperties->height);
    // Keep running until term
    static  Time frameTime = Time::seconds(1.f/30.f);
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
            usleep((unsigned int)(frameTime - fTime).asMicroseconds());
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
