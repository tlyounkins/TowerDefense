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
    float x;
    float y;
    
    // Public interface
    
    float get_x_location();
    void set_x_location(float x);
    
    float get_y_location();
    void set_y_location(float y);
    
    int get_enemy_health();
    void set_enemy_health(int enemy_health);
    
    //void get_color()
    //void set_color(color);
    void draw();
    void step();
    
    int get_speed();
    void set_speed(int speed);
};

#endif /* EnemyModel_hpp */
