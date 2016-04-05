//
//  GameController.cpp
//  Zombie Tower Defense
//


#include "GameController.hpp"

// Constructor
GameController::GameController() {
    endgame = false;
}

// Destructor
GameController::~GameController() {
    
}

// Start Game
void GameController::startGame() {
    printf("Game Started\n");
    startLevel();
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
}

// End level
void GameController::endLevel() {
    printf("Level ended\n");
}

// Update total_points
void GameController::update_total_points() {
    game_model.total_points++;
}

void GameController::damageCastle(int damage) {
    int health = castle.get_castle_health();
    health--;
    if (health <= 0) {
        endGame();
    } else {
        castle.set_castle_health(health);
    }
    
}