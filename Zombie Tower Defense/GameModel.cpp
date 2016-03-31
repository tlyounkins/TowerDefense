//
//  GameModel.cpp
//  Zombie Tower Defense
//


#include "GameModel.hpp"

// Constructor
GameModel::GameModel()
{
    total_points = 0;
    wave_num = 1;
    current_level = 1;
    
    //levels[0] = new LevelModel(0, 2);
    levels.create_level(5);
}

// Destructor
GameModel::~GameModel() {
    
}

int GameModel::get_wave_num() {
    return wave_num;
}

void GameModel::set_wave_num(int wave_num) {
    this->wave_num = wave_num;
}

