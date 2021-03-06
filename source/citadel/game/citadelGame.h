//
//  citadelGame.h
//  Floating Citadel Demo app
//
//  Created by Norman van der Ploeg on 2020-01-17.
//  Copyright © 2020 Floating Citadel Games. All rights reserved.
//

#ifndef citadelGame_h
#define citadelGame_h

namespace citadel {

class GameConfig;

class CitadelGame {
public:
    CitadelGame();
    ~CitadelGame() = default;
    int run();
    
    
private:
    bool ready;
    Clock clock;
    std::shared_ptr<GameConfig> gameConfig;
    void Tick(Time &deltaTime);
};

} //namespace citadel.
#endif /* citadelGame_h */
