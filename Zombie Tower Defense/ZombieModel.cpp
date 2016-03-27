//
//  ZombieModel.cpp
//  Zombie Tower Defense
//


#include "ZombieModel.hpp"

// Constructor
ZombieModel::ZombieModel() {
    this->count = 0;
}

// Destructor
ZombieModel::~ZombieModel() {
    
}

// Update zombie location method
void ZombieModel::step(){
    // Head towards (0, -5)
    this->count += 1;
    if(count == this->speed){
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
    
        // Print current coordinates (for testing)
        //printf("%i %i \n", this->x, this->y);
        this->count = 0;
    }
}