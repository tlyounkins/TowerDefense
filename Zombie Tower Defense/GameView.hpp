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

class GameView {
    
public:
    // Constructor, destructor
    GameView();
    ~GameView();
    
    // Variables
  
    
    // Public interface
    void test();
    int Initialize(int argc, char *argv[]);
    // TODO: Make these non-static functions
    void static display();
    void static keyFunc(unsigned char key, int x, int y);

};
#endif /* GameView_hpp */
