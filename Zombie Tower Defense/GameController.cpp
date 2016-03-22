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

// Start Game
void GameController::startGame(int argc, char *argv[]) {
    view.Initialize(argc, argv);
    //view.test();
    printf("Game Started\n");
    startLevel();
}

// End Game
void GameController::endGame() {
    printf("GAME OVER\n");
    GameModel model;
    int level = model.current_level;
    int wave = model.wave_num;
    int total_points = model.total_points;
    printf("Total points: %i\n",total_points);
    printf("Game ended on level: %i\n",level);
    printf("Game ended on wave: %i\n",wave);
}

// Start level
void GameController::startLevel() {
    printf("Level started\n");
    start_wave(0, 0);
}

// End level
void GameController::endLevel() {
    printf("Level ended\n");
}

// Start Wave
void GameController::start_wave(int wave_num, int level){
    printf("Wave %i starting\n", wave_num);
    for(int i = 0; i < 5; i++){
        view.draw_zombie(game.levels.wave_enemies[0][i]);
    }
    for(int i = 0; i < 5; i++){
        game.levels.wave_enemies[0][i].step();
    }
    
}

// Update total_points
void GameController::update_total_points() {
    GameModel model;
    model.total_points++;
}

void GameController::damageCastle(int damage) {
    CastleModel castle;
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