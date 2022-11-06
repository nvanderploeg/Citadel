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
#include <chrono>
#include <thread>
#include <cassert>

//lib includes
#include "GLFW/glfw3.h"

//Citadel includes
#include "citadelSystem.h"
#include "citadelGame.h"
#include "gameConfig.h"
#include "windowProperties.h"

#include "input/inputRouter.h"

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
    m_gameConfig = make_shared<GameConfig>("game.config");
    if (!glfwInit()) {
        // Initialization failed
        cout << "Failed to init glfw" << endl;
    }
    else {
        ready = true;
    }
}

void CitadelGame::Setup() {

    auto width = m_gameConfig->windowProperties->width;
    auto height = m_gameConfig->windowProperties->height;

    //Make the App window!
    m_window = glfwCreateWindow(width, height, 
                                          m_gameConfig->windowProperties->title.c_str(), NULL, NULL);

    if (!m_window) {
        throw(std::runtime_error("Couldn't make window!"));
    }

    //Create and bind the input router for event handling
    m_inputRouter = std::make_shared<InputRouter>();
    m_inputRouter->BindToGLFW(m_window);

    glfwMakeContextCurrent(m_window);
    initGL(width, height);
}

void CitadelGame::TearDown() {
    assert(m_window); 
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

bool CitadelGame::Running() {
    return !glfwWindowShouldClose(m_window);
}

int CitadelGame::run() {
    if (!ready) {
        return 500; //Failed to init
    }

    Setup();
    // Keep running until term
    static  Time frameTime = Time::seconds(1.f/30.f);
    Time frameTimer = Time::getCurrentTime();
    clock.restart();
    while (Running())
    {
        //Do Tick(Update objects)
        auto delta = clock.restart();
        
        if (delta.asSeconds() > 0.1) { // Just too long, lets reset
            delta = clock.restart();
        }

        Tick(delta);
        
        glfwSwapBuffers(m_window);
        glfwPollEvents();
        
        auto fTime = clock.getElapsedTime();
        if(fTime < frameTime) {
            std::this_thread::sleep_for(std::chrono::microseconds((unsigned int)(frameTime - fTime).asMicroseconds()));
        }
    }

    TearDown();
    
    return kSuccess;
}


void CitadelGame::Tick(Time &deltaTime) {
    // std::cout << deltaTime.asSeconds() << std::endl;
}

} //namespace citadel
