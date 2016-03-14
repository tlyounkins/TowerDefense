//
//  ZombieModel.hpp
//  Zombie Tower Defense
//


#ifndef ZombieModel_hpp
#define ZombieModel_hpp

#include <stdio.h>

class ZombieModel: public EnemyModel {
    
public:
    // Constructor, destructor
    ZombieModel(int health, int speed, float x, float y);
    ~ZombieModel();
    
    // Variables
    GLUquadricObj *quadric;
    float x_coor;
    float y_coor;
    // Public interface
    void step();
};

#endif /* ZombieModel_hpp */
