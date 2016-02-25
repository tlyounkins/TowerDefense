//
//  GameView.cpp
//  Zombie Tower Defense
//
//  Created by Michael Fioravanti on 2/8/16.
//
//

#include "GameView.hpp"

// Constructor
GameView::GameView() {
    
}

// Destructor
GameView::~GameView() {
    
}

// Display Callback
void GameView::display() {
    
    // Reset background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Flush Buffer
    glFlush();
    
    // Swap Buffers
    glutSwapBuffers();
}

void GameView::test() {
    printf("Test works!/n");
}
int GameView::Initialize(int argc, char *argv[]) {
    // Initialize GLUT
    glutInit(&argc, argv);
    
    // Initialize the window with double buffering and RGB colors
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    // Set window size
    glutInitWindowSize(512, 512);
    
    // Create WIndow
    glutCreateWindow("Tower Defense");
    
#ifndef OSX
    // Initialize GLEW
    glewInit();
#endif
    
    // Define Callbacks
    // TODO: Fix this
    glutDisplayFunc(display);
    
    // Set Background Color
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    // Begin event loop
    glutMainLoop();
    
    return 0;
}



