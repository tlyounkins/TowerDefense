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
            int x_pos, y_pos = 0;
            // Switches
            int location = rand() % 8;
            
            switch(location){
                // Case 1 - Top - Left
                case 0:
                    x_pos = -20;
                    y_pos = rand() % 20;
                    break;
                    
                // Case 2 - Top - Top-Left
                case 1:
                    x_pos = rand() % 20;
                    x_pos = -x_pos;
                    
                    y_pos = 20;
                    break;
                    
                // Case 3 - Top - Top-Right
                case 2:
                    x_pos = rand() % 20;
                    
                    y_pos = 20;
                    break;
                    
                // Case 4 - Top - Right
                case 3:
                    x_pos = 20;
                    
                    y_pos = rand() % 20;
                    break;
                    
                // Case 5 - Bottom - Right
                case 4:
                    x_pos = -20;
                    
                    y_pos = rand() % 20;
                    y_pos = -y_pos;
                    break;
                    
                // Case 6 - Bottom - Bottom Right
                case 5:
                    x_pos = rand() % 20;
                    
                    y_pos = -20;
                    break;
                    
                // Case 7 - Bottom - Bottom Left
                case 6:
                    x_pos = rand() % 20;
                    x_pos = -x_pos;
                    
                    y_pos = -20;
                    break;
                    
                // Case 8 - Bottom - Left
                case 7:
                    x_pos = -20;
                    
                    y_pos = rand() % 20;
                    y_pos = -y_pos;
                    break;
            };
            
            ZombieModel zombie;
            zombie.health = 10;
            zombie.speed = 20;
            zombie.x = x_pos;
            zombie.y = y_pos;
            wave_enemies[i][j] = zombie;
            
        }
    }
}
