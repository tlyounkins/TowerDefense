//
//  ZombieModel.cpp
//  Zombie Tower Defense
//


#include "ZombieModel.hpp"

// Constructor
ZombieModel::ZombieModel(int health, int speed, float x, float y) {
    x_coor = x;
    y_coor = y;
}

// Destructor
ZombieModel::~ZombieModel() {
    
}

// Update zombie location method
void ZombieModel::step(){
    // Head towards (0, -0.25)
    float x = this->x_coor;
    float y = this->y_coor;
    
    int ran = rand() % 10;
    if(ran < 5){
        if(x > 0){
            x -= 0.001;
        } else if(x < 0){
            x += 0.001;
        }
    } else{
        if(y > -0.25){
            y -= 0.001;
        } else if(y < -0.25){
            y += 0.001;
        }
    }
    this->x_coor = x;
    this->y_coor = y;
    
    printf("%f %f \n", this->x_coor, this->y_coor);
    
    glutPostRedisplay();
}