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
void LevelModel::create_level(int waves, int game_map[]){
    this->waves = waves;
    
    srand(time(NULL));
    for(int i = 0; i < waves; i++) {
        create_wave(i, game_map);
    }
}

// create Wave
void LevelModel::create_wave(int wave_number, int game_map[]){
    for(int j = 0; j < 15; j++){
        create_wave_enemy(wave_number, j, game_map);
    }

}

// Because astart is BEING A LITTLE BITCH
void LevelModel::create_wave_enemy(int wave_number, int wave_position, int game_map[]){
    int x_pos, y_pos = 0;
    // Switches
    
    int location =  rand() % 8;
    
    switch(location){
            // Case 1 - Top - Left
        case 0:
            x_pos = 1;
            y_pos = rand() % 20;
            break;
            
            // Case 2 - Top - Top-Left
        case 1:
            x_pos = rand() % 20;
            
            y_pos = 20;
            break;
            
            // Case 3 - Top - Top-Right
        case 2:
            x_pos = (rand() % 20) + 18;
            
            y_pos = 20;
            break;
            
            // Case 4 - Top - Right
        case 3:
            x_pos = 38;
            
            y_pos = rand() % 20;
            break;
            
            // Case 5 - Bottom - Right
        case 4:
            x_pos = 38;
            
            y_pos = (rand() % 20) + 18;
            break;
            
            // Case 6 - Bottom - Bottom Right
        case 5:
            x_pos = (rand() % 20) + 18;
            
            y_pos = 38;
            break;
            
            // Case 7 - Bottom - Bottom Left
        case 6:
            x_pos = rand() % 20;
            
            y_pos = 38;
            break;
            
            // Case 8 - Bottom - Left
        case 7:
            x_pos = 1;
            
            y_pos = (rand() % 20)+18;
            break;
    }
    
    ZombieModel zombie;
    zombie.health = 10;
    zombie.speed = 20;
    zombie.x = x_pos;
    zombie.y = y_pos;
    printf("create %i, %i\n", wave_number, wave_position);
    zombie.create_path(wave_number, wave_position, game_map);
    printf("placing %i, %i\n", wave_number, wave_position);
    this->wave_enemies[wave_number][wave_position] = zombie;
    printf("done %i\n", wave_position);

}
