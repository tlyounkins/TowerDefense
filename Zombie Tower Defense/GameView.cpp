//
//  GameView.cpp
//  Zombie Tower Defense
//


#include "GameView.hpp"

// Zombie object
ZombieModel zombie(10, 1, 0.9, -0.8);

// Draw Castle
CastleModel castle;

// Upgrades tower object
UpgradesModel tower;

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

    draw_zombie();
    zombie.step();
    
    castle.draw();
    tower.draw_tower();
    
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

// Draw zombie method
void GameView::draw_zombie() {
    zombie.quadric = gluNewQuadric();
    gluQuadricDrawStyle(zombie.quadric, GLU_FILL);
    gluQuadricNormals(zombie.quadric, GLU_SMOOTH);
    
    
    glPushAttrib(GL_CURRENT_BIT);
    glPushMatrix();
    glTranslatef(zombie.x_coor, zombie.y_coor, 0.0f);
    glColor3f(0.2f, 0.8f, 0.2f);
    glScalef(0.01, 0.01, 1);
    gluDisk(zombie.quadric, 0, 2, 100, 100);
    glColor3f(0.0f, 0.0f, 0.0f);
    gluDisk(zombie.quadric, 1.9, 2, 100, 100);
    glPopMatrix();
    glPopAttrib();
}