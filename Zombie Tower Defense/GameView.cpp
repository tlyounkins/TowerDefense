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
    GameView view;
    view.draw_zombie();
    zombie.step();
    
    view.draw_castle();
    view.draw_tower();
    
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

void GameView::draw_grid() {
    
    
}

// Draw zombie method
void GameView::draw_zombie() {
    zombie_quadric = gluNewQuadric();
    gluQuadricDrawStyle(zombie_quadric, GLU_FILL);
    gluQuadricNormals(zombie_quadric, GLU_SMOOTH);
    
    
    glPushAttrib(GL_CURRENT_BIT);
    glPushMatrix();
    glTranslatef(zombie.x_coor, zombie.y_coor, 0.0f);
    glColor3f(0.2f, 0.8f, 0.2f);
    glScalef(0.01, 0.01, 1);
    gluDisk(zombie_quadric, 0, 2, 100, 100);
    glColor3f(0.0f, 0.0f, 0.0f);
    gluDisk(zombie_quadric, 1.9, 2, 100, 100);
    glPopMatrix();
    glPopAttrib();
}

void GameView::draw_castle() {
    glPushAttrib(GL_CURRENT_BIT);
    glPushMatrix();
    glColor3f(0.5f, 0.5f, 0.5f);
    glScalef(0.25, 0.25, 1.0);
    glBegin(GL_POLYGON);
    // Counter-ClockWise around origin
    // Top Left
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    // Do not fill polygon
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);
    // Top Left
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glEnd();
    // Revert Changes
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPopMatrix();
    glPopAttrib();
}

void GameView::draw_tower() {
    tower_quadric = gluNewQuadric();
    gluQuadricDrawStyle(tower_quadric, GLU_FILL);
    gluQuadricNormals(tower_quadric, GLU_SMOOTH);
    
    
    glPushAttrib(GL_CURRENT_BIT);
    glPushMatrix();
    glTranslatef(0.25, -0.25, 0.0f);
    glColor3f(0.75f, 0.75f, 0.75f);
    glScalef(0.03, 0.03, 1);
    gluDisk(tower_quadric, 0, 2, 100, 100);
    glColor3f(0.0f, 0.0f, 0.0f);
    gluDisk(tower_quadric, 1.9, 2, 100, 100);
    glPopMatrix();
    glPopAttrib();
}