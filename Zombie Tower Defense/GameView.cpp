//
//  GameView.cpp
//  Zombie Tower Defense
//


#include "GameView.hpp"
ZombieModel zombie;
// Draw Castle
CastleModel castle;

// Constructor
GameView::GameView() {
    
}

// Destructor
GameView::~GameView() {
    
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
    glutInitWindowSize(1000, 1000);
    
    // Create WIndow
    glutCreateWindow("Tower Defense");
    
#ifndef OSX
    // Initialize GLEW
    glewInit();
#endif
    
    // Define Callbacks
    glutDisplayFunc(display);
    glutKeyboardFunc(keyFunc);
    
    // Set Background Color
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    // TEMP TO TEST
    zombie.set_x_location(1);
    zombie.set_y_location(-0.8);
    
    // Begin event loop
    glutMainLoop();
    
    return 0;
}

// Display Callback
void GameView::display() {
    
    // Reset background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Flush Buffer
    glFlush();

    zombie.draw();
    zombie.step();
    
    castle.draw();
    
    
    
    // Swap Buffers
    glutSwapBuffers();
}

// Keyboard Callback
void GameView::keyFunc(unsigned char key, int x, int y) {
    // Exit Program with ESC
    // Temp until menu works
    if (key == 27){
        printf("Main needs to exit!");
        exit(0);
    }
}