//
//  TowerModel.hpp
//  Zombie Tower Defense
//
//  Created by Michael Fioravanti on 4/10/16.
//
//

#ifndef TowerModel_hpp
#define TowerModel_hpp

#include <stdio.h>
class TowerModel {
    
public:
    // Constructor, destructor
    TowerModel();
    ~TowerModel();
    
    // Variables
    int x;
    int y;
    int game_x;
    int game_y;
    int range;
    
    // Save hit location
    int enemy_x;
    int enemy_y;
    bool hit;
    
    // Tower can only fire so often
    // Higher the speed, slower the fire rate
    int speed;
    int cooldown;
    
    // Public interface
    void draw_hit();
};

#endif /* TowerModel_hpp */
