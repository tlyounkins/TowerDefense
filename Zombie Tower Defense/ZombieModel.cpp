//
//  ZombieModel.cpp
//  Zombie Tower Defense
//


#include "ZombieModel.hpp"

// Constructor
ZombieModel::ZombieModel(int health, int speed, float x, float y) {
    x_coor = x;
    y_coor = y;
    this->speed = speed;
    count = 0;
}

// Destructor
ZombieModel::~ZombieModel() {
    
}

// Update zombie location method
void ZombieModel::step(){
    // Head towards (0, -5)
    this->count += 1;
    if(count == this->speed){
        float x = this->x_coor;
        float y = this->y_coor;
        
        int ran = rand() % 10;
        if(ran < 5){
            if(x > 0){
                x -= 1;
            } else if(x < 0){
                x += 1;
            } else {
                // Can only move y
                if(y > -5){
                    y -= 1;
                } else if(y < -5){
                    y += 1;
                }
            }
        } else{
            if(y > -5){
                y -= 1;
            } else if(y < -5){
                y += 1;
            } else {
                // Can only move x
                if(x > 0){
                    x -= 1;
                } else if(x < 0){
                    x += 1;
                }
            }
        }
        this->x_coor = x;
        this->y_coor = y;
    
        // Print current coordinates (for testing)
        printf("%f %f \n", this->x_coor, this->y_coor);
        this->count = 0;
    }
    
    glutPostRedisplay();
}