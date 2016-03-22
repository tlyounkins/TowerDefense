//
//  LevelModel.cpp
//  Zombie Tower Defense
//
//  Created by Michael Fioravanti on 3/21/16.
//
//

#include "LevelModel.hpp"
// Constructor
LevelModel::LevelModel() {
}

// Destructor
LevelModel::~LevelModel() {
    
}

// Create Level
void LevelModel::create_level(int waves){
    this->waves = waves;
    
    for(int i = 0; i < waves; i++) {
        for(int j = 0; j < 5; j++){
            int x_pos = rand() % 20;
            int y_pos = rand() % 20;
            
            
            ZombieModel zombie(10, 20, x_pos, y_pos);
            wave_enemies[i][j] = zombie;
        }
    }
}
