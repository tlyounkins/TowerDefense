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
#include "stlastar.h"
#include "findpath.cpp"

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
    int path_length;
    int path_location;
    bool left, right, down, up;
    AStarSearch<MapSearchNode> astarsearch;
    MapSearchNode *path[];

    // Public interface
    virtual void step();
    void create_path(int i, int j, int game_map[]);
};

#endif /* ZombieModel_hpp */
