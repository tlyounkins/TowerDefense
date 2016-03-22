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
    levels.create_level(2);
}

// Destructor
GameModel::~GameModel() {
    
}

