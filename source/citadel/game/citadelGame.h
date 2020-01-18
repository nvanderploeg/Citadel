//
//  citadelGame.h
//  Floating Citadel Demo app
//
//  Created by Norman van der Ploeg on 2020-01-17.
//  Copyright © 2020 Floating Citadel Games. All rights reserved.
//

#ifndef citadelGame_h
#define citadelGame_h

#include <iostream>

namespace citadel {

class CitadelGame {
public:
    CitadelGame() { }
    
    int run() { std::cout << "hello world!" << std::endl;
        return 0;
    }
};

} //namespace citadel.
#endif /* citadelGame_h */
