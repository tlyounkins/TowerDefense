//
//  GameView.hpp
//  Zombie Tower Defense
//


#ifndef GameView_hpp
#define GameView_hpp

#ifdef OSX
    #include <GLUT/glut.h>
#else
    #include <GL/glew.h>
    #include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EnemyModel.hpp"
#include "ZombieModel.hpp"
#include "CastleModel.hpp"
#include "UpgradesModel.hpp"
#include "GameController.hpp"



class GameView {
    
public:
    // Constructor, destructor
    GameView();
    ~GameView();
    
    // Variables
    GLUquadricObj *quadric;
    int ADD_TOWER;
    
    // Grid size
    int x_max;
    int y_max;
   
    // Public interface
    void test();
    int Initialize(int argc, char *argv[]);
    void static idleFunc();
    void static display();
    void static keyFunc(unsigned char key, int x, int y);
    void static draw_current_enemies();
    void static draw_zombie(EnemyModel zombie);
    void static draw_grid();
    void static draw_castle();
    void static draw_tower();
    void draw_wave(int wave_num, int level);
    void static upgrades_menu(int id);
    void static draw_text();
    void static mousefunc(int button, int state, int x, int y);
    void static movefunc(int x, int y);
    
};
#endif /* GameView_hpp */
