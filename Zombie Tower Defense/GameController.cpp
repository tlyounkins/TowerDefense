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
    GameView view;
    view.Initialize(argc, argv);
    //view.test();
    printf("Game Started\n");
}

// End Game
void GameController::endGame() {
    printf("GAME OVER\n");
    GameModel model;
    int level = model.level;
    int wave = model.wave_num;
    int total_points = model.total_points;
    printf("Total points: %i\n",total_points);
    printf("Game ended on level: %i\n",level);
    printf("Game ended on wave: %i\n",wave);
}

// Start level
void GameController::startLevel() {
    
}

// End level
void GameController::endLevel() {
    
}

// Update total_points
int GameController::update_total_points() {

}

void GameController::damageCastle(int damage) {
    CastleModel castle;
    int health = castle.get_castle_health();
    if (health <= 0) {
        endGame();
    }
}

void GameController::spawn_enemy(int wave_num, int level) {
   // EnemyModel enemy = new EnemyModel();
}