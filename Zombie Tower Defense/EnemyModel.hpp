//
//  EnemyModel.hpp
//  Zombie Tower Defense
//


#ifndef EnemyModel_hpp
#define EnemyModel_hpp

#include <stdio.h>
#ifdef OSX
    #include <GLUT/glut.h>
#else
    #include <GL/glew.h>
    #include <GL/glut.h>
#endif

class EnemyModel {
    
public:
    // Constructor, destructor
    EnemyModel();
    ~EnemyModel();
    
    // Variables
    int enemy_health;
    int speed;
    GLUquadricObj *quadric;
    
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
    void set_enemy_health(int health);
    
    //void get_color()
    //void set_color(color);
    void draw();
    virtual void step(int map[][40]);
    
    int get_speed();
    void set_speed(int speed);
    
    void create_path();
};

#endif /* EnemyModel_hpp */
