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

int GameModel::get_level() {
    return current_level;
}

void GameModel::set_level(int level) {
    this->current_level = level;
}

int GameModel::get_num_resources() {
    return num_resources;
}

void GameModel::set_num_resources(int num_resources) {
    this->num_resources = num_resources;
}
