//
//  GameController.hpp
//  Zombie Tower Defense
//
//  Created by Juan A. Salazar on 2/8/16.
//
//

#ifndef GameController_hpp
#define GameController_hpp

#include <stdio.h>

template <class T>
class GameModel {
    
public:
    // Constructor, destructor
    GameMode();
    ~GameModel();
    
    // Variables
    int total_points;
    
    // Public interface (GameModel's functions)
    void startGame();
    void endGame();
    void startLevel();
    void endLevel();
    int update_total_points();
};

#endif /* GameController_hpp */
