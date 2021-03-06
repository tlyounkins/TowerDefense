//
//  LevelModel.hpp
//  Zombie Tower Defense
//
//  Created by Michael Fioravanti on 3/21/16.
//
//

#ifndef LevelModel_hpp
#define LevelModel_hpp

#include <stdio.h>
#include <stdlib.h> 
#include <ctime>
#include "EnemyModel.hpp"
#include "ZombieModel.hpp"

class LevelModel {
    
public:
    // Constructor, destructor
    LevelModel();
    ~LevelModel();
    
    // Variables
    int id;
    int wave_amount;
    ZombieModel wave_enemies[5000][5000];
    
    
    // Public interface
    void create_level(int waves, int level);
};

#endif /* LevelModel_hpp */
