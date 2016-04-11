//
//  Main.cpp
//  Zombie Tower Defense
//


#include "GameController.hpp"
#include "GameController.cpp"
#include "GameView.hpp"
#include "GameView.cpp"

#ifdef OSX
    #include <GLUT/glut.h>
#else
    #include <GL/glew.h>
    #include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>

// Function Prototypes
void keyFunc(unsigned char key, int x, int y);

int main(int argc, char *argv[]) {
    // Start Game
    GameView game;
    game.Initialize(argc, argv);

    return 0;
}

// Keyboard Callback
void keyFunc(unsigned char key, int x, int y) {
    // Exit Program with ESC
    // Temp until menu works
    if (key == 27){
        //exit(0);
    }
}