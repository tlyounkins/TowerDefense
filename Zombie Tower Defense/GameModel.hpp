//
//  GameModel.hpp
//  Zombie Tower Defense
//


#ifndef GameModel_hpp
#define GameModel_hpp

#include <stdio.h>
#include "LevelModel.hpp"
#include "LevelModel.cpp"

class GameModel {

public:
    // Constructor, destructor
    GameModel();
    ~GameModel();
    
    // Variables
    int total_points;
    int wave_num;
    int current_level;
    //LevelModel levels[8];
    LevelModel levels;
   
    
    // Public interface (GameModel's functions)
    
};
#endif /* GameModel_hpp */
