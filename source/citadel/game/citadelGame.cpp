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
#include <filesystem>

//lib includes
#include "GLFW/glfw3.h"

//Citadel includes
#include "citadelSystem.h"
#include "citadelGame.h"
#include "gameConfig.h"
#include "windowProperties.h"

#include "input/inputRouter.h"

using namespace std;

namespace
{
    const std::string DEFAULT_CONFIGURATIONFILENAME = "game.cfg";
}

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
    Init(DEFAULT_CONFIGURATIONFILENAME);
}

CitadelGame::CitadelGame(filesystem::path& configPath)
{
    if (!configPath.has_filename())
    {
        // TODO logging
        cout << "WARNING: Configuration file not specified; using \"" << DEFAULT_CONFIGURATIONFILENAME<< "\"." << endl;
        configPath.replace_filename(DEFAULT_CONFIGURATIONFILENAME);
    }

    Init(configPath);
}

bool CitadelGame::Init(const filesystem::path& configPath)
{
    // TODO use a logging system
    cout << "== INIT ==\n";
    m_ready = true;
    m_gameConfig = make_shared<GameConfig>(configPath);
    
    if (!glfwInit())
    {
        // Initialization failed
        m_ready = false;
        // TODO use a logging system
        cout << "ERROR: Failed to init glfw\n";
    }

    // TODO use a logging system
    cout << "ok." << endl;
    return m_ready;
}

void CitadelGame::Setup()
{
    // TODO use a logging system
    cout << "== SETUP ==\n";

    auto width = m_gameConfig->windowProperties->width;
    auto height = m_gameConfig->windowProperties->height;

    //Make the App window!
    m_window = glfwCreateWindow(width, height, 
                                          m_gameConfig->windowProperties->title.c_str(), NULL, NULL);

    if (!m_window) {
        // TODO use a logging system
        throw(std::runtime_error("Couldn't make window!"));
    }

    //Create and bind the input router for event handling
    m_inputRouter = std::make_shared<InputRouter>();
    m_inputRouter->BindToGLFW(m_window);

    // load the input mappings from a file defined in the gameConfig
    Json::Value jContext = Serializer::loadFile(m_gameConfig->inputContext);
    m_inputRouter->SetInputContext(jContext);

    // bind a callback (lambda in this case) to an event label
    m_inputRouter->BindCallbackToLabel("moveUp", [this](InputEventData data)
    {
        std::cout << "movin' on up!\n";
        return true;
    });

    glfwMakeContextCurrent(m_window);
    initGL(width, height);

    // TODO use a logging system
    cout << "ok." << endl;

}

void CitadelGame::TearDown() {
    // TODO: logging
    cout << "== TEAR DOWN ==" << endl;

    // save out the current configurations
    bool savedInputContext = m_inputRouter->Save();
    cout << "Saving InputContext.. ";
    cout << (savedInputContext ? "ok." : "error.") << endl;
    cout << "Saving GameConfig.. ";
    bool savedGameConfig = m_gameConfig->Save();
    cout << (savedGameConfig ? "ok." : "error.") << endl;

    assert(m_window);
    glfwDestroyWindow(m_window);
    glfwTerminate();

    // TODO: logging
    cout << "ok." << endl;
}

bool CitadelGame::Running() {
    return !glfwWindowShouldClose(m_window);
}

int CitadelGame::run() {
    if (!m_ready) {
        return 500; //Failed to init
    }

    Setup();

    // TODO: logging
    cout << "== RUNNING ==" << endl;

    // bind a termination request to the escape key
    m_inputRouter->AddEventWithCallback("terminate", { GLFW_KEY_ESCAPE, GLFW_PRESS, 0 }, [this](InputEventData& data) {
        cout << "Escape pressed, Terminating..." << endl;
        glfwSetWindowShouldClose(m_window, true);
        return true;
    });

    // Keep running until term
    static  Time frameTime = Time::seconds(1.f/m_gameConfig->windowProperties->maxFPS);
    Time frameTimer = Time::getCurrentTime();
    m_clock.restart();
    while (Running())
    {
        //Do Tick(Update objects)
        auto delta = m_clock.restart();
        
        if (delta.asSeconds() > 0.1) { // Just too long, lets reset
            delta = m_clock.restart();
        }

        Tick(delta);
        
        glfwSwapBuffers(m_window);
        glfwPollEvents();
        
        auto fTime = m_clock.getElapsedTime();
        if(fTime < frameTime) {
            std::this_thread::sleep_for(std::chrono::microseconds((unsigned int)(frameTime - fTime).asMicroseconds()));
        }
    }

    // TODO: logging
    cout << "run complete." << endl;


    TearDown();
    
    return kSuccess;
}


void CitadelGame::Tick(Time &deltaTime) {
    // std::cout << deltaTime.asSeconds() << std::endl;
}

} //namespace citadel
