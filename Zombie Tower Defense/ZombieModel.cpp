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
void ZombieModel::step(int map[][40]){
    // Head towards (20, 25)
    int current_x = this->x;
    int current_y = this->y;
    int next_x = 0;
    int next_y = 0;
    //this->count += 1;
    //if(count == this->speed){
        // For testing
        //printf("location: %i, length: %i\n", this->path_location, this->path_length);
        
        // Print current coordinates (for testing)
        //printf("%i %i \n", this->x, this->y);
        int ran = rand() % 10;
        if(ran < 5){
            if(current_x > 20){
                next_x = current_x - 1;
                next_y = current_y;
            } else if(current_x < 20){
                next_x = current_x + 1;
                next_y = current_y;
            } else {
                // Can only move y
                if(current_y > 25){
                    next_y = current_y - 1;
                    next_x = current_x;
                } else if(current_y < 25){
                    next_y = current_y + 1;
                    next_x = current_x;
                }
            }
        } else{
            if(current_y > 25){
                next_y = current_y - 1;
                next_x = current_x;
            } else if(current_y < 25){
                next_y = current_y + 1;
                next_x = current_x;
            } else {
                // Can only move x
                if(current_x > 20){
                    next_x = current_x - 1;
                    next_y = current_y;
                } else if(current_x < 20){
                    next_x = current_x + 1;
                    next_y = current_y;
                }
            }
        }
        // TODO: Split grid into 4 coordinates
        // 15 15 - 25 15   Top Middle
        // Collison move right
        // 15 25 - 15 15   Left Middle
        // Collision move down
        // 25 15 - 25 25   Right Middle
        // Collision Mode down
        // 25 25 - 15 25   Bottom Middle
        // Collision move depending on x
        //  < 20 -> move right
        //  > 20 -> move left
        if(map[next_y][next_x] == 9){
            // Top Middle
            if((current_x <= 25) && (current_y <= 15)){
                next_x = current_x + 1;
                next_y = current_y;
            }
            // Left Middle
            else if((current_x <= 15) && (current_y <=25)) {
                next_x = current_x;
                next_y = current_y - 1;
            }
            // Right Middle
            else if((current_x >= 25) && (current_y <= 25)){
                    next_x = current_x;
                    next_y = current_y - 1;
            }
            // Bottom Middle
            else if((current_x <= 20) && (current_y >= 25)){
                next_x = current_x + 1;
                next_y = current_y;
            }
            else if((current_x >= 20) && (current_y >= 25)){
                next_x = current_x + 1;
                next_y = current_y;
            }
    
        }
        /**if(map[next_y][next_x] == 9){
            // Top Left
            if((current_x < 20) && (current_y < 20)){
                // If encountering a nine going right, go down
                if(next_x != current_x){
                    next_x = current_x;
                    next_y = current_y + 1;
                }
                // If encountering a nine going down, go left
                if(next_y != current_y){
                    next_x = current_x - 1;
                    next_y = current_y;
                }
            }
            // Top Right
            else if((current_x >= 20) && (current_y < 20)){
                // If encountering a nine going left, go down
                if(next_x != current_x){
                    next_x = current_x;
                    next_y = current_y + 1;
                }
                // If encountering a nine going down, go right
                if(next_y != current_y){
                    next_x = current_x + 1;
                    next_y = current_y;
                }
            }
            // Bottom Right
            else if((current_x >= 20) && (current_y >= 20)){
                // If encountering a nine going left, go down
                if(next_x != current_x){
                    next_x = current_x;
                    next_y = current_y + 1;
                }
                // If encountering a nine going up, go left
                if(next_y != current_y){
                    next_x = current_x - 1;
                    next_y = current_y;
                }
            }
            // Bottom Left
            else{
                // If encountering a nine going right, go down
                if(next_x != current_x){
                    next_x = current_x;
                    next_y = current_y + 1;
                }
                // If encountering a nine going up, go right
                if(next_y != current_y){
                    next_x = current_x + 1;
                    next_y = current_y;
                }
            }
        }
        //printf("Next_x, Next_y: %i, %i  Map: %i\n", next_x, next_y, map[next_y][next_x]);
        //int ran = rand() % 10;
        // Quadrant 0: Top Left
        if((current_x < 20) && (current_y < 20)){
            // Go Right
            if(ran < 5){
                next_x = current_x + 1;
                next_y = current_y;
            }
            // Go Down
            else{
                next_x = current_x;
                next_y = current_y + 1;
            }
    
            // Check for Collisions
            if(map[next_y][next_x] == 9){
                // If encountering a nine going right, go down
                if(next_x != current_x){
                    next_x = current_x;
                    next_y = current_y + 1;
                }
                // If encountering a nine going down, go left
                if(next_y != current_y){
                    next_x = current_x - 1;
                    next_y = current_y;
                }
            }
        }
        // Quadrant 1: Top Right
        else if((current_x >= 20) && (current_y < 20)){
            //Go Left, Unless at 20
            if(ran < 5){
                if(current_x != 20){
                    next_x = current_x - 1;
                    next_y = current_y;
                }
                // Head down instead
                else {
                    next_x = current_x;
                    next_y = current_y + 1;
                }
            }
            // Go Down
            else{
                next_x = current_x;
                next_y = current_y + 1;
            }
            
            // Check for Collisions
            if(map[next_y][next_x] == 9){
                // If encountering a nine going left, go down
                if(next_x != current_x){
                    next_x = current_x;
                    next_y = current_y + 1;
                }
                // If encountering a nine going down, go right
                if(next_y != current_y){
                    next_x = current_x + 1;
                    next_y = current_y;
                }
            }
        }
        // Quadrant 2: Bottom Right
        else if((current_x >= 20) && (current_y >= 20)){
            // Go Left, Unless at 20
            if(ran < 5){
                if(current_x != 20){
                    next_x = current_x - 1;
                    next_y = current_y;
                }
                // Less than 25
                else if(current_y < 25){
                    next_x = current_x;
                    next_y = current_y - 1;
                }
                // Greater than 25
                else{
                    next_x = current_x;
                    next_y = current_y + 1;
                }
            }
            // Go Up, Unless at 25
            else{
                // Go Right if at 25
                if(current_y == 25){
                    next_x = current_x + 1;
                    next_y = current_y;
                }
                // Less than 25
                else if(current_y < 25){
                    next_x = current_x;
                    next_y = current_y - 1;
                }
                // Greater than 25
                else{
                    next_x = current_x;
                    next_y = current_y + 1;
                }
            }
            
            // Check for Collisions
            if(map[next_y][next_x] == 9){
                // If encountering a nine going left, go down
                if(next_x != current_x){
                    next_x = current_x;
                    next_y = current_y - 1;
                }
                // If encountering a nine going up, go left
                if(next_y != current_y){
                    next_x = current_x + 1;
                    next_y = current_y;
                }
            }
        }
        // Quadrant 3: Bottom Left
        else{
            // Go Right
            if(ran < 5){
                next_x = current_x + 1;
                next_y = current_y;
            }
            // Go Up
            else{
                if(current_y < 25){
                    next_x = current_x;
                    next_y = current_y - 1;
                } else{
                    next_x = current_x;
                    next_y = current_y + 1;
                }
            }
            
            // Check for Collisions
            if(map[next_y][next_x] == 9){
                // If encountering a nine going right, go down
                if(next_x != current_x){
                    next_x = current_x;
                    next_y = current_y + 1;
                }
                // If encountering a nine going up, go right
                if(next_y != current_y){
                    next_x = current_x;
                    next_y = current_y - 1;
                }
            }
        }**/
        
        this->x = next_x;
        this->y = next_y;
        this->count = 0;
    //}
}