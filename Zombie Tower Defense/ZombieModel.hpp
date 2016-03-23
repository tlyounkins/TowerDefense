//
//  ZombieModel.hpp
//  Zombie Tower Defense
//


#ifndef ZombieModel_hpp
#define ZombieModel_hpp

#include <stdio.h>
#ifdef OSX
    #include <GLUT/glut.h>
#else
    #include <GL/glew.h>
    #include <GL/glut.h>
#endif

class ZombieModel: public EnemyModel {
    
public:
    // Constructor, destructor
    ZombieModel();
    ~ZombieModel();
    
    // Variables
    GLUquadricObj *quadric;
    int count;
    int health;
    int speed;
    // Public interface
    virtual void step();
};

#endif /* ZombieModel_hpp */
