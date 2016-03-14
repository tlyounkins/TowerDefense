//
//  EnemyModel.cpp
//  Zombie Tower Defense
//
//  Created by Tyler Younkins on 2/8/16.
//
//

#include "EnemyModel.hpp"

// Constructor
EnemyModel::EnemyModel() {

}

// Destructor
EnemyModel::~EnemyModel() {
    
}

int EnemyModel::get_enemy_health() {
    return enemy_health;
}

void EnemyModel::set_enemy_health(int health) {
    this->enemy_health = health;
}

int EnemyModel::get_speed() {
    return speed;
}

void EnemyModel::set_speed(int speed) {
    this->speed = speed;
}

float EnemyModel::get_x_location() {
    return x;
}
void EnemyModel::set_x_location(float x) {
    this->x = x;
}

float EnemyModel::get_y_location() {
    return y;
}
void EnemyModel::set_y_location(float y) {
    this->y = y;
}

void EnemyModel::draw(){
    
}

void EnemyModel::step(){
    
}