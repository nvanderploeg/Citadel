//
//  citadelGame.h
//  Floating Citadel Demo app
//
//  Created by Norman van der Ploeg on 2020-01-17.
//  Copyright © 2020 Floating Citadel Games. All rights reserved.
//

#ifndef citadelGame_h
#define citadelGame_h

class GLFWwindow;

namespace citadel {

class GameConfig;
class InputRouter;
class VulkanGraphics;
class Camera;
class Scene;
class CitadelGame;

class CitadelGameDelegate 
{
public:
    virtual ~CitadelGameDelegate() = default;
    virtual void OnGameDidFinishInitialization(CitadelGame* game) = 0;
};

class CitadelGame
{
public:
    CitadelGame(const std::filesystem::path& configPath, const std::shared_ptr<CitadelGameDelegate>& delegate);
    ~CitadelGame() = default;
    int run();
    
    void SetScene(const std::shared_ptr<Scene>& scene);
    
protected:
    bool m_ready;
    Clock m_clock;
    std::shared_ptr<GameConfig> m_gameConfig;
    std::shared_ptr<Camera> m_camera;
    std::shared_ptr<CitadelGameDelegate> m_delegate;

    std::shared_ptr<Scene> m_currentScene;
public: 
    std::shared_ptr<InputRouter> m_inputRouter;
    virtual void Tick(Time &deltaTime);
    virtual void Draw();

private:
    GLFWwindow* m_window;
    bool Init(const std::filesystem::path& configPath);
    void Setup();
    void TearDown();

    bool Running();
};

} //namespace citadel.
#endif /* citadelGame_h */
