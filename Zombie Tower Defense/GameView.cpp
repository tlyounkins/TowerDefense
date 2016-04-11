//
//  GameView.cpp
//  Zombie Tower Defense
//


#include "GameView.hpp"
#define SIZE 500
#define N 3

GameController game;

GLUquadricObj *tower_quadric;

int max = 5;
bool Tower_flag1 = false;
ZombieModel current_enemies[5];

char healthStr[32];
char waveStr[32];
char levelStr[32];
GLint start_x = 0;
GLint start_y = 0;
GLfloat tower_x = 0.0f;
GLfloat tower_y = 0.0f;

// Global animation variables
GLint fps = 30;
GLint time = 0;
GLint lasttime = 0;

// Conversion from screen to world coordinates
GLfloat dt = 0.05f;

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
    glutMouseFunc(mousefunc);
    glutMotionFunc(movefunc);
    
    // Set Background Color
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    // Create Game Controller
    game.startGame();
    
    //Temp?
    for(int i = 0; i < max; i++){
        current_enemies[i] = game.game_model.levels.wave_enemies[0][i];
    }
    
    // Create upgrades men
    glutCreateMenu(upgrades_menu);
    glutAddMenuEntry("Add Tower",ADD_TOWER);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    // Begin event loop
    glutMainLoop();
    
    return 0;
}

// Glorious Idle Function
void GameView::idleFunc(){
    
    // Time-based Animations
    time = glutGet(GLUT_ELAPSED_TIME);
    
    // Update if past desired interval
    if (time - lasttime > 1000.0f/fps)
    {
        
        int count = 0;
        // Move Zombies
        for(int i = 0; i < max; i++){
            // Check zombie location
            if((current_enemies[i].x == 0) && (current_enemies[i].y == -5)){
                // Zombie made it to castle
                current_enemies[i].x = 0;
                current_enemies[i].y = 0;
                // Damage Castle
                int health = game.castle.get_castle_health();
                health--;
                printf("Your castle takes damage!\n");
                game.castle.set_castle_health(health);
                printf("Castle health is now %i\n",health);
                if (health <= 0) {
                    printf("\n\n");
                    game.endGame();
                    exit(0);
                }
            } else {
                if((current_enemies[i].x == 0)&&(current_enemies[i].y == 0)){
                    count++;
                } else {
                current_enemies[i].step();
                }
            }
        }

        // Next Wave
        if (count == max){
            printf("Next Wave!\n");
          

            int wave = game.game_model.get_wave_num();
            if (wave == 2) {
                int level = game.game_model.get_level();
                level++;
                game.game_model.set_level(level);
                game.startLevel();
                game.castle.set_castle_health(20);
            } else {
                wave++;
                game.game_model.set_wave_num(wave);
            }
            printf("game_model.get_wave_num() = %i\n",game.game_model.get_wave_num());
            for(int i = 0; i < max; i++){
                current_enemies[i] = game.game_model.levels.wave_enemies[wave][i];
            }
        }
    
        // Update lasttime (reset time)
        lasttime = time;
    
        glutPostRedisplay();
    }
}

// Display Callback
void GameView::display() {
    
    // Reset background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-20.0f, 20.0f, -20.0f, 20.0f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Flush Buffer
    glFlush();
    
    //draw objects
    draw_objects(GL_RENDER);
    
    if (Tower_flag1 == true)
    {
        draw_tower();
    }

    
    // Swap Buffers
    glutSwapBuffers();
}

// Keyboard Callback
void GameView::keyFunc(unsigned char key, int x, int y)
{
    // Exit Program with ESC
    // Temp until menu works
    if (key == 27) {
        printf("Main needs to exit!\n");
        exit(0);
    }
}

// Mouse click callback
void GameView::mousefunc(int button, int state, int x, int y)
{
    GLuint nameBuffer[SIZE];
    GLint hits;
    GLint viewport[4];
    
    // Store cursor position when left button is clicked
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        start_x = x;
        start_y = y;
    }
    
    // Store cursor position when left button is clicked
    if(button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
    {
        start_x = x;
        start_y = y;
        //initialize the name stack
        glInitNames();
        glPushName(0);
        glSelectBuffer(SIZE,nameBuffer);
        
        //view for selection mode
        glGetIntegerv(GL_VIEWPORT,viewport);
        glMatrixMode(GL_PROJECTION);
        
        //Save original viewing matrix
        glPushMatrix();
            glLoadIdentity();
        
            //NxN pick area
            //Invert y to get in world coord
            gluPickMatrix((GLdouble) x ,(GLdouble)(viewport[3] - y) ,N ,N, viewport);
        
            gluOrtho2D(-20.0f, 20.0f, -20.0f, 20.0f);
        
            glRenderMode(GL_SELECT);
            draw_objects(GL_SELECT);
            glMatrixMode(GL_PROJECTION);
        
        //restore viewing matrix
        glPopMatrix();
        
        //return to normal rendering
        hits = glRenderMode(GL_RENDER);
        
        //process hits from selection mode
        processHits(hits,nameBuffer);
         printf("Hits processed!!\n");
        
        //normal render
        glutPostRedisplay();
    }
    
}

// Mouse move callback
void GameView::movefunc(int x, int y)
{
    GLint dx, dy;
    
    // Compute change in cursor position (inverted y)
    dx = x - start_x;
    dy = start_y - y;
    
    /*
     TODO: add changes here to make the picking work
    */
    
    
    // Update Tower (bounded) position
    tower_x += dx*dt;
    if (tower_x < -19.0f)
    {
        tower_x = -19.0f;
    }
    else if (tower_x > 19.0f)
    {
        tower_x = 19.0f;
    }
    
    tower_y += dy*dt;
    if (tower_y < -19.0f)
    {
        tower_y = -19.0f;
    }
    else if (tower_y > 19.0f)
    {
        tower_y = 19.0f;
    }
    
    // Reset start position
    start_x = x;
    start_y = y;
    
    // Redraw screen
    glutPostRedisplay();
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
void GameView::upgrades_menu(int id) {
    Tower_flag1 = true;
}

// Routine to draw text on screen
void GameView::draw_text() {
    glPushMatrix();
    glLoadIdentity();
    
    // Create strings
    sprintf(healthStr,"Castle Health:  %d",game.castle.get_castle_health());
    sprintf(levelStr,"Level:  %d",game.game_model.get_level()+1);
    sprintf(waveStr,"Wave:  %d",game.game_model.get_wave_num()+1);
    glColor3f(1.0f,0.0f,0.0f);
    // Set the text to the top left corner
    glRasterPos2f(-18.0f,17.0f);
    for (unsigned int i = 0; i<strlen(healthStr); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, healthStr[i]);
    }
    glRasterPos2f(-18.0f,16.0f);
    for (unsigned int i = 0; i<strlen(levelStr); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, levelStr[i]);
    }
    glRasterPos2f(-18.0f,15.0f);
    for (unsigned int i = 0; i<strlen(waveStr); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, waveStr[i]);
    }
    
    glPopMatrix();
    
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

void GameView::draw_castle()
{
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

void GameView::draw_tower()
{
    tower_quadric = gluNewQuadric();
    gluQuadricDrawStyle(tower_quadric, GLU_FILL);
    gluQuadricNormals(tower_quadric, GLU_SMOOTH);
    
    glPushAttrib(GL_CURRENT_BIT);
    glPushMatrix();
        //glTranslatef(4, -4, 0.0f);
        glTranslatef(tower_x,tower_y, 0.0f);
        glColor3f(0.75f, 0.75f, 0.75f);
        //glScalef(0.03, 0.03, 1);
        gluDisk(tower_quadric, 0, 1.5, 100, 100);
        glColor3f(0.0f, 0.0f, 0.0f);
        gluDisk(tower_quadric, 1.4, 1.5, 100, 100);
        // Firing Range
        glColor3f(1.0f, 0.0f, 0.0f);
        gluDisk(tower_quadric, 2.4, 2.5, 100, 100);
    glPopMatrix();
}

void GameView::draw_objects(GLenum mode)
{
    //draw selections
    if(mode == GL_RENDER){ glLoadName(1);
        draw_text();
    }
    //printf("Hey it drew text!\n");
    if(mode == GL_RENDER){ glLoadName(2);
        draw_grid();
    }
     //printf("Hey it drew grid!\n");
    if(mode == GL_RENDER){ glLoadName(3);
        draw_current_enemies();
    }
     //printf("Hey it drew enemy!\n");
    if(mode == GL_RENDER){ glLoadName(4);
        draw_castle();
    }
    if(mode == GL_SELECT){ glLoadName(5);
        if (Tower_flag1 == true) {
           // mode = GL_SELECT;
            draw_tower();
            printf("Draw plz\n");
        }
    }
     //printf("Hey it drew castle!\n");
    
}
void GameView::processHits(GLint hits, GLuint buffer[]){
    
    unsigned int i, j;
    GLuint names, *ptr;
    
    printf("hits = %d\n",hits);
    
    ptr = (GLuint *) buffer;
    
    //loops over hits
    for(i = 0; i < hits; i++)
    {
        names = *ptr;
        
        //skip over number of names and depths
        ptr += 3;
        
        //check each name
        
        for(j = 0;  j < names; j++)
        {
            if(*ptr == 1) printf("zombies, castles, and lines\n");
            else printf("other\n");
            
            //next hit
            ptr++;
        }
    }
}


// Start Wave
void GameView::draw_wave(int wave_num, int level)
{
    printf("Wave %i starting\n", wave_num);
    for(int i = 0; i < max; i++){
        draw_zombie(game.game_model.levels.wave_enemies[wave_num][i]);
    }
    for(int i = 0; i < max; i++){
        //game.game_model.levels.wave_enemies[wave_num][i].step();
    }
    
}