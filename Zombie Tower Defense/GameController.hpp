//
//  GameController.hpp
//  Zombie Tower Defense
//
//  Created by Juan A. Salazar on 2/8/16.
//
//

#ifndef GameController_hpp
#define GameController_hpp

#include "GameView.hpp"
#include "GameView.cpp"

#include <stdio.h>

class GameController {
    
public:
    // Constructor, destructor
    GameController();
    ~GameController();
    
    // Variables
    int total_points;
    
    // Public interface
    void startGame(int argc, char *argv[]);
    void endGame();
    void startLevel();
    void endLevel();
    void pause_game();
    int update_total_points();
};

#endif /* GameController_hpp */
