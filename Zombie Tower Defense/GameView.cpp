//
//  GameView.cpp
//  Zombie Tower Defense
//


#include "GameView.hpp"

// Zombie object
ZombieModel zombie(10, 20, 15, -19);
// TEMP TO TEST
ZombieModel zombie_test(0, 20, -15, -10);

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
    
    
    // Begin event loop
    glutMainLoop();
    
    return 0;
}

// Display Callback
void GameView::display() {
    
    // Reset background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0f, 20.0f, -20.0f, 20.0f, 0.0f, 1.0f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Flush Buffer
    glFlush();
    
    draw_grid();

    draw_zombie(zombie_test);
    draw_zombie(zombie);
    
    zombie_test.step();
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
        printf("Main needs to exit!\n");
        exit(0);
    }
}
// Draw Grid
void GameView::draw_grid(){
    for(int i = -20; i <= 20; i++){
        // Draw Vertical Lines
        glPushAttrib(GL_CURRENT_BIT);
        glPushMatrix();
            if(i == 0){
                glColor3f(1.0f,0.0f, 0.0f);
            } else {
                glColor3f(0.0f, 0.0f, 0.0f);
            }
            glBegin(GL_LINES);
                glVertex3f(i, 20.0, 0.0);
                glVertex3f(i, -20.0, 0.0);
            glEnd();
        glPopAttrib();
        glPopMatrix();
    }
    for (int j = -20; j <= 20; j++) {
        // Draw Horizontal Lines
        glPushAttrib(GL_CURRENT_BIT);
        glPushMatrix();
            if(j == 0){
                glColor3f(0.0f, 1.0f, 0.0f);
            } else {
                glColor3f(0.0f, 0.0f, 0.2f);
            }
            glBegin(GL_LINES);
                glVertex3f(20.0, j, 0.0);
                glVertex3f(-20.0, j, 0.0);
            glEnd();
        glPopAttrib();
        glPopMatrix();
    }
}
// Draw zombie method
void GameView::draw_zombie(ZombieModel zombie) {
    zombie.quadric = gluNewQuadric();
    gluQuadricDrawStyle(zombie.quadric, GLU_FILL);
    gluQuadricNormals(zombie.quadric, GLU_SMOOTH);
    
    
    glPushAttrib(GL_CURRENT_BIT);
    glPushMatrix();
        glTranslatef(zombie.x_coor, zombie.y_coor, 0.0f);
        glColor3f(0.2f, 0.8f, 0.2f);
        //glScalef(0.01, 0.01, 1);
        gluDisk(zombie.quadric, 0, 0.5, 100, 100);
        glColor3f(0.0f, 0.0f, 0.0f);
        gluDisk(zombie.quadric, 0.47, 0.5, 100, 100);
    glPopMatrix();
    glPopAttrib();
}