//
//  Main.cpp
//  Zombie Tower Defense
//
//  Created by Tyler Younkins on 2/8/16.
//
//

#include "GameController.hpp"
#include "GameController.cpp"

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
    GameController game;
    game.startGame(argc, argv);

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