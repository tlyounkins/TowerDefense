//
//  GameView.hpp
//  Zombie Tower Defense
//
//  Created by Michael Fioravanti on 2/8/16.
//
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

class GameView {
    
public:
    // Constructor, destructor
    GameView();
    ~GameView();
    
    // Variables
  
    
    // Public interface
    void display();
    void test();
    int Initialize(int argc, char *argv[]);
    
    
};
#endif /* GameView_hpp */
