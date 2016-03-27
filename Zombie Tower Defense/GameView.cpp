//
//  GameView.cpp
//  Zombie Tower Defense
//


#include "GameView.hpp"

GameController game;

GLUquadricObj *tower_quadric;

int max = 5;
int wave = 0;

ZombieModel current_enemies[5];



// Constructor
GameView::GameView() {
    
}

// Destructor
GameView::~GameView() {
    
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
    glutIdleFunc(idleFunc);
    
    // Set Background Color
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    // Create Game Controller
    game.startGame();
    
    //Temp?
    for(int i = 0; i < max; i++){
        current_enemies[i] = game.game_model.levels.wave_enemies[0][i];
    }
    
    // Create upgrades men
    //glutCreateMenu(upgrades_menu);
    //glutAddMenuEntry("Tower",ADD_TOWER);
    //glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    // Begin event loop
    glutMainLoop();
    
    return 0;
}

// Glorious Idle Function
void GameView::idleFunc(){
    int count = 0;
    // Move Zombies
    for(int i = 0; i < max; i++){
        // Check zombie location
        if((current_enemies[i].x == 0) && (current_enemies[i].y == -5)){
            // Zombie made it to castle
            current_enemies[i].x = 0;
            current_enemies[i].y = 0;
            // Damage Castle
            
        } else {
            if((current_enemies[i].x == 0)&&(current_enemies[i].y == 0)){
                count++;
            } else {
                current_enemies[i].step();
            }
        }
    }
    
    // Next Wave
    if(count == max){
        printf("Next Wave!\n");
        wave++;
        for(int i = 0; i < max; i++){
            current_enemies[i] = game.game_model.levels.wave_enemies[wave][i];
        }
    }
    glutPostRedisplay();
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
    
    draw_current_enemies();
    
    draw_castle();
    draw_tower();
    
    
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
                 
// Draw Current Enemies
void GameView::draw_current_enemies(){
    for(int i = 0; i < max; i++){
        draw_zombie(current_enemies[i]);
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

// Routine to process upgrades menu selection
void upgrades_menu(int id)
{
    
}

// Draw zombie method
void GameView::draw_zombie(EnemyModel zombie) {
    zombie.quadric = gluNewQuadric();
    gluQuadricDrawStyle(zombie.quadric, GLU_FILL);
    gluQuadricNormals(zombie.quadric, GLU_SMOOTH);
    
    //printf("Drawing at (%i, %i)\n", zombie.x, zombie.y);
    
    glPushAttrib(GL_CURRENT_BIT);
    glPushMatrix();
        glTranslatef(zombie.x, zombie.y, 0.0f);
        glColor3f(0.2f, 0.8f, 0.2f);
        gluDisk(zombie.quadric, 0, 0.5, 100, 100);
        glColor3f(0.0f, 0.0f, 0.0f);
        gluDisk(zombie.quadric, 0.47, 0.5, 100, 100);
    glPopMatrix();
    glPopAttrib();
}

void GameView::draw_castle() {
    glPushAttrib(GL_CURRENT_BIT);
    glPushMatrix();
        glColor3f(0.5f, 0.5f, 0.5f);
        glBegin(GL_POLYGON);
            // Counter-ClockWise around origin
            // Top Left
            glVertex3f(-5.0f, 5.0f, 0.0f);
            glVertex3f(-5.0f, -5.0f, 0.0f);
            glVertex3f(5.0f, -5.0f, 0.0f);
            glVertex3f(5.0f, 5.0f, 0.0f);
        glEnd();
        glColor3f(0.0f, 0.0f, 0.0f);
        // Do not fill polygon
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_POLYGON);
        // Top Left
            glVertex3f(-5.0f, 5.0f, 0.0f);
            glVertex3f(-5.0f, -5.0f, 0.0f);
            glVertex3f(5.0f, -5.0f, 0.0f);
            glVertex3f(5.0f, 5.0f, 0.0f);
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
        glTranslatef(4, -4, 0.0f);
        glColor3f(0.75f, 0.75f, 0.75f);
        //glScalef(0.03, 0.03, 1);
        gluDisk(tower_quadric, 0, 1.5, 100, 100);
        glColor3f(0.0f, 0.0f, 0.0f);
        gluDisk(tower_quadric, 1.4, 1.5, 100, 100);
    glPopMatrix();
    glPopAttrib();
}

// Start Wave
void GameView::draw_wave(int wave_num, int level){
    printf("Wave %i starting\n", wave_num);
    for(int i = 0; i < max; i++){
        draw_zombie(game.game_model.levels.wave_enemies[wave_num][i]);
    }
    for(int i = 0; i < max; i++){
        //game.game_model.levels.wave_enemies[wave_num][i].step();
    }
    
}