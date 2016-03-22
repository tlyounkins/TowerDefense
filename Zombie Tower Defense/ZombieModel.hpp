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
    ZombieModel(int health, int speed, int x, int y);
    ~ZombieModel();
    
    // Variables
    GLUquadricObj *quadric;
    int count;
    // Public interface
    void step();
};

#endif /* ZombieModel_hpp */
