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
#include "EnemyModel.hpp"
#include "ZombieModel.hpp"

class LevelModel {
    
public:
    // Constructor, destructor
    LevelModel();
    ~LevelModel();
    
    // Variables
    int id;
    int waves;
    EnemyModel wave_enemies[10][5];
    
    
    // Public interface
    void create_level(int waves);
};

#endif /* LevelModel_hpp */
