//
//  GameController.hpp
//  Zombie Tower Defense
//


#ifndef GameController_hpp
#define GameController_hpp

#include "GameView.hpp"
#include "GameView.cpp"
#include "GameModel.hpp"
#include "GameModel.cpp"
#include "CastleModel.hpp"
#include "CastleModel.cpp"
#include "EnemyModel.hpp"
#include "EnemyModel.cpp"
#include "ZombieModel.hpp"
#include "ZombieModel.cpp"
#include "UpgradesModel.hpp"
#include "UpgradesModel.cpp"

#include <stdio.h>

class GameController {
    
public:
    // Constructor, destructor
    GameController();
    ~GameController();
    
    // Variables
    
    // Public interface
    void startGame(int argc, char *argv[]);
    void endGame();
    void startLevel();
    void endLevel();
    void pause_game();
    int update_total_points();
    void damageCastle(int damage);
    void spawn_enemy(int wave_num, int level);
};

#endif /* GameController_hpp */
