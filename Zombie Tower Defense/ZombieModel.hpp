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
    ZombieModel();
    ~ZombieModel();
    
    // Variables
    GLUquadricObj *quadric;
    
    // Public interface
    void draw();
   
};

#endif /* ZombieModel_hpp */
