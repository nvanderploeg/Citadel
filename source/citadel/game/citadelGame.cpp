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
#include "glm/glm.hpp"

//Citadel includes
#include "citadelSystem.h"
#include "citadelGame.h"
#include "gameConfig.h"
#include "camera.h"
#include "graphics.h"
#include "windowProperties.h"

#include "input/inputRouter.h"

#include "scene.h"
#include "gameObject.h"
#include "component.h"
#include "transformComponent.h"

using namespace std;

namespace
{
    const std::string DEFAULT_CONFIGURATIONFILENAME = "game.cfg";
}

namespace citadel {

CitadelGame::CitadelGame(const filesystem::path& configPath, const std::shared_ptr<CitadelGameDelegate>& delegate)
:m_delegate(delegate)
{
    if (configPath.has_filename())
    {
        Init(configPath);
       
    } else {
        // TODO logging
        cout << "WARNING: Configuration file not specified; using \"" << DEFAULT_CONFIGURATIONFILENAME<< "\"." << endl;
        Init(DEFAULT_CONFIGURATIONFILENAME);
    }
}

bool CitadelGame::Init(const filesystem::path& configPath)
{
    // TODO use a logging system
    cout << "== INIT ==\n";
    m_ready = true;
    m_gameConfig = make_shared<GameConfig>(configPath);
    m_graphics = make_shared<VulkanGraphics>();
    m_camera = make_shared<Camera>();

    if (!glfwInit())
    {
        // Initialization failed
        m_ready = false;
        // TODO use a logging system
        cout << "ERROR: Failed to init glfw\n";
    }

    // TODO use a logging system
    cout << "Init: ok." << endl;
    return m_ready;
}

void CitadelGame::Setup()
{
    // TODO use a logging system
    cout << "== SETUP ==\n";

    auto width = m_gameConfig->windowProperties->width;
    auto height = m_gameConfig->windowProperties->height;

    //Make the App window!
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

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

    // test binding for mouse click
    m_inputRouter->BindCallbackToLabel("mouseClick", [this](InputEventData data)
    {
        std::cout << "mouse button up\n";
        return true;
    });

    glfwMakeContextCurrent(m_window);
    m_graphics->InitVulkan(m_window);
    m_graphics->SetFoV(fieldOfView);


    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window,int width, int height) {
        //TODO: magic a way to call the graphics that a resize happened
    });
    
    m_inputRouter->BindCallbackToLabel("MouseScroll", [this](InputEventData data) {
        auto& scrollData = std::get<MouseScrollEventData>(data);
        if (scrollData.yOffset != 0) {
               
            fieldOfView += (scrollData.yOffset > 0) ? 5 : -5;
            fieldOfView = std::max(45.f, fieldOfView);
            fieldOfView = std::min(120.f, fieldOfView);
            m_graphics->SetFoV(fieldOfView);
            return true;
        }
        return false;
    });

    // TODO use a logging system
    cout << "SETUP ok." << endl;

    if (m_delegate) {
        m_delegate->OnGameDidFinishInitialization(this);
    }
}

void CitadelGame::TearDown() 
{
    // TODO: logging
    cout << "== TEAR DOWN ==" << endl;

    // save out the current configurations
    bool savedInputContext = m_inputRouter->Save();
    cout << "Saving InputContext.. ";
    cout << (savedInputContext ? "ok." : "error.") << endl;
    cout << "Saving GameConfig.. ";
    bool savedGameConfig = m_gameConfig->Save();
    cout << (savedGameConfig ? "ok." : "error.") << endl;

    m_graphics->Cleanup();
    assert(m_window);
    glfwDestroyWindow(m_window);
    glfwTerminate();

    // TODO: logging
    cout << "ok." << endl;
}

void CitadelGame::SetScene(const std::shared_ptr<Scene>& scene)
{
    m_currentScene = scene;
}

bool CitadelGame::Running() 
{
    return !glfwWindowShouldClose(m_window);
}

int CitadelGame::run() 
{
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
    static Time frameTime = Time::seconds(1.f/m_gameConfig->windowProperties->maxFPS);
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
        glfwPollEvents();
        Draw();
        
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


void CitadelGame::Tick(Time &deltaTime) 
{
    //Update game scenes!
    if (m_currentScene) {
        m_currentScene->Tick(deltaTime);
    }
}

void CitadelGame::Draw() 
{
    //Compile frame
    m_graphics->SetViewMatrix(m_camera->GetViewMatrix());

    if (m_currentScene) {
        m_currentScene->Draw();
    }

    //Tell the graphics engine to render it!
    m_graphics->DrawFrame();
}
} //namespace citadel
