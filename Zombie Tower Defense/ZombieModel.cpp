//
//  ZombieModel.cpp
//  Zombie Tower Defense
//


#include "ZombieModel.hpp"

// Constructor
ZombieModel::ZombieModel() {
    this->count = 0;
    this->right= true;
    this->left=true;
    this->up=true;
    this->path_location = 0;
    this->down=true;
    this->visible = true;
    this->health = 1;
}

// Destructor
ZombieModel::~ZombieModel() {
    
}

// Update zombie location method
void ZombieModel::step(){
    // Head towards (20, 25)
    int current_x = this->x;
    int current_y = this->y;
    this->count += 1;
    if(count == this->speed){
        // For testing
        //printf("location: %i, length: %i\n", this->path_location, this->path_length);
        
        // For Astar algorithm
        /**if(this->path_location < this->path_length){
            this->path[path_location]->x = this->x;
            this->path[path_location]->y = this->y;
            this->path_location++;
        }**/
    
        // Print current coordinates (for testing)
        //printf("%i %i \n", this->x, this->y);
        int ran = rand() % 10;
        if(ran < 5){
            if(current_x > 20){
                this->x -= 1;
            } else if(current_x < 20){
                this->x += 1;
            } else {
                // Can only move y
                if(current_y > 25){
                    this->y -= 1;
                } else if(current_y < 25){
                    this->y += 1;
                }
            }
        } else{
            if(current_y > 25){
                this->y -= 1;
            } else if(current_y < 25){
                this->y += 1;
            } else {
                // Can only move x
                if(current_x > 20){
                    this->x -= 1;
                } else if(current_x < 20){
                    this->x += 1;
                }
            }
        }
        
        this->count = 0;
    }
}