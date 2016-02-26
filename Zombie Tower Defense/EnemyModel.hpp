//
//  EnemyModel.hpp
//  Zombie Tower Defense
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
    int enemy_health;
    int speed;
    // TODO: some color variable(s) -> R, G, B?
    
    // Location Variables
    int x;
    int y;
    
    // Public interface
    
    int get_x_location();
    void set_x_location(int x);
    
    int get_y_location();
    void set_y_location(int y);
    
    int get_enemy_health();
    void set_enemy_health(int enemy_health);
    
    //void get_color()
    //void set_color(color);
    
    int get_speed();
    void set_speed(int speed);
};

#endif /* EnemyModel_hpp */
