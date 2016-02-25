//
//  EnemyModel.hpp
//  Zombie Tower Defense
//
//  Created by Tyler Younkins on 2/8/16.
//
//

#ifndef EnemyModel_hpp
#define EnemyModel_hpp

#include <stdio.h>

class EnemyModel {
    
public:
    // Constructor, destructor
    EnemyModel();
    ~EnemyModel();
    
    // Variables
    int health;
    int speed;
    // TODO: some color variable(s) -> R, G, B?
    int x;
    int y;
    
    // Public interface
    
    // get_location();
    //void set_location(int x, int y);
    
    int get_health();
    void set_health(int health);
    
    //void get_color()
    //void set_color(color);
    
    int get_speed();
    void set_speed(int speed);
};

#endif /* EnemyModel_hpp */
