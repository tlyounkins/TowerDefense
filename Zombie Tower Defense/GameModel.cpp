//
//  GameModel.cpp
//  Zombie Tower Defense
//


#include "GameModel.hpp"

// Constructor
GameModel::GameModel()
{
    total_points = 0;
    wave_num = 0;
    current_level = 0;
    
    //levels[0] = new LevelModel(0, 2);
}

// Destructor
GameModel::~GameModel() {
    
}

void GameModel::create_levels(int game_map[]){
    levels.create_level(1, game_map);
}

int GameModel::get_wave_num() {
    return wave_num;
}

void GameModel::set_wave_num(int wave_num) {
    this->wave_num = wave_num;
}

