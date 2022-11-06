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

class CitadelGame {
public:
    CitadelGame();
    ~CitadelGame() = default;
    int run();
    
    
protected:
    bool ready;
    Clock clock;
    std::shared_ptr<GameConfig> m_gameConfig;
    std::shared_ptr<InputRouter> m_inputRouter;
    virtual void Tick(Time &deltaTime);

private:
    GLFWwindow* m_window;
    void Setup();
    void TearDown();

    bool Running();

};

} //namespace citadel.
#endif /* citadelGame_h */
