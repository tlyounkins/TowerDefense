//
//  GameController.cpp
//  Zombie Tower Defense
//


#include "GameController.hpp"

// Constructor
GameController::GameController() : game_model(){
    endgame = false;
}

// Destructor
GameController::~GameController() {
    
}

//Set Up Game
void GameController::game_setup(){
    printf("Creating game\n");
    //num_enemies = 5;
    //game_model.create_levels(num_enemies);
    startLevel();
    game_model.set_total_points(0);
}

// End Game
void GameController::endGame() {
    endgame = true;
    printf("GAME OVER\n");
    int level = game_model.current_level;
    int wave = game_model.get_wave_num();
    int total_points = game_model.total_points;
    printf("Total points: %i\n",total_points);
    printf("Game ended on level: %i\n",level);
    printf("Game ended on wave: %i\n",wave);
}

// Start level
void GameController::startLevel() {
    printf("Level started\n");
    game_model.set_wave_num(0);
    int level = game_model.get_level();
    num_enemies = (level+1) * 5;
    game_model.create_levels(num_enemies);
    printf("Level: %i, Number of enemies: %i\n", level+1, num_enemies);
    // Update starting resources for level
    game_model.set_num_resources((level + 1) * 500);
}

// End level
void GameController::endLevel() {
    printf("Level ended\n");
}

// Update total_points
void GameController::update_total_points() {
    int points = game_model.get_total_points();
    points++;
    game_model.set_total_points(points);
}
