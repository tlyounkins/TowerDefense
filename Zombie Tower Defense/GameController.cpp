//
//  GameController.cpp
//  Zombie Tower Defense
//


#include "GameController.hpp"

// Constructor
GameController::GameController() {
   
}

// Destructor
GameController::~GameController() {
    
}

//Set Up Game
void GameController::game_setup(int game_map[]){
    game_model.create_levels(game_map);
}

// Start Game
void GameController::startGame() {
    //view.test();
    printf("Game Started\n");
    startLevel();
}

// End Game
void GameController::endGame() {
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
    health = health - damage;
    if (health <= 0) {
        endGame();
    } else {
        castle.set_castle_health(health);
    }
}

void GameController::spawn_enemy(int wave_num, int level) {
   // EnemyModel enemy = new EnemyModel();
}