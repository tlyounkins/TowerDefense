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
            bool done = false;
            while(!done){
                int x_pos = rand() % 20;
                int y_pos = rand() % 20;
            
                int neg_x = rand()%100;
                int neg_y = rand()%100;
            
                if(neg_x <= 50){
                    x_pos = -x_pos;
                }
                if(neg_y <= 50){
                    y_pos = -y_pos;
                }
                
                if(((x_pos <= 5) && (x_pos >= -5)) && ((y_pos <=5) && (y_pos >= -5))){
                    done = false;
                } else{
                    done = true;
                    ZombieModel zombie;
                    zombie.health = 10;
                    zombie.speed = 20;
                    zombie.x = x_pos;
                    zombie.y = y_pos;
                    wave_enemies[i][j] = zombie;
                }
            }
        }
    }
}
