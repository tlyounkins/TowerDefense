//
//  GameView.cpp
//  Zombie Tower Defense
//


#include "GameView.hpp"
#define SIZE 500
#define N 3

#define add_tower 0
#define castle_health_increase 1
#define add_moat 2

GameController *game;
UpgradesModel upgrades;
GLUquadricObj *tower_quadric;

int enemy_max;
int tower_max = 5;
int current_towers = 0;
bool Tower_flag1 = false;
bool Moat_flag = false;
ZombieModel current_enemies[500];
TowerModel active_towers[5];
// 0 empty, 9 impassable
// SWAP Y AND X'S FOR THE LOVE OF THOR
int grid_location[40][40] = {
//   0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9
    {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},//0
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//1
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//2
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//3
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//4
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//5
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//6
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//7
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//8
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//9
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//10
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//11
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//12
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//13
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//14
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,9,9,9,9,9,9,9,9,9,9,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//15
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//16
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//17
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//18
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//19
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//20
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//21
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//22
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//23
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//24
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,9,9,9,9,0,9,9,9,9,9,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//25
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//26
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//27
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//28
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//29
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//30
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//31
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//32
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//33
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//34
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//35
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//36
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//37
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//38
    {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9}//39
    
};

// GRID FORMULA -> ((y*40)+x)

char healthStr[32];
char resourcesStr[32];
char pointsStr[32];
char waveStr[32];
char levelStr[32];
char gameoverStr[32];
char continueStr[32];
char yesnoStr[32];
GLfloat start_x = 0.0f;
GLfloat start_y = 0.0f;
GLfloat tower_x = 0.0f;
GLfloat tower_y = 0.0f;
int start_hit_x = 0.0;
int start_hit_y = 0.0;
int end_hit_x = 0.0;
int end_hit_y = 0.0;
// Global animation variables
GLint fps = 90;
GLint current_time;
GLint lasttime;

// Conversion from screen to world coordinates
GLfloat dt = 0.04f;

// Constructor
GameView::GameView(){
    
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

    //print_array();
    
    
    // Create Game Controller
    game = new GameController();
    
    game->game_setup();
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
    glClearColor(0.0f, 0.75f, 0.0f, 1.0f);

    
    //Temp?
    for(int i = 0; i < game->num_enemies; i++){
        current_enemies[i] = game->game_model.levels.wave_enemies[0][i];
    }
    
    // Create upgrades men
    glutCreateMenu(upgrades_menu);
    glutAddMenuEntry("Add Tower: 500 resources",add_tower);
    glutAddMenuEntry("Increase Castle Health by 5: 500 resources",castle_health_increase);
    glutAddMenuEntry("Add Moat: 1000 resources",add_moat);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    // Begin event loop
    glutMainLoop();
    
    return 0;
}

// Glorious Idle Function
void GameView::idleFunc(){
    
    // Time-based Animations
    current_time = glutGet(GLUT_ELAPSED_TIME);
    
    // Update if past desired interval
    if (current_time - lasttime > 1000.0f/fps)
    {
        //enemy_max = game->num_enemies;
        int count = 0;
        // Pew Pew
        check_tower_proximity();
        
        // Move Zombies
        for(int i = 0; i < game->num_enemies; i++){
            // Check zombie location
            if((current_enemies[i].x == 20) && (current_enemies[i].y == 25)){
                // Zombie made it to castle
                current_enemies[i].x = 0;
                current_enemies[i].y = 0;
                // Damage Castle
                int health = game->castle.get_castle_health();
                health--;
                printf("Your castle takes damage!\n");
                game->castle.set_castle_health(health);
                printf("Castle health is now %i\n",health);
                if (health <= 0) {
                    printf("\n\n");
                    game->endGame();
                }
            } else {
                if(((current_enemies[i].x == 0)&&(current_enemies[i].y == 0))||(!current_enemies[i].visible)){
                    count++;
                } else if (game->endgame == false) {
                    grid_location[current_enemies[i].y][current_enemies[i].x] = 0;
                    current_enemies[i].step();
                    grid_location[current_enemies[i].y][current_enemies[i].x] = 9;
                }
            }
        }
       
        // Next Wave
        if (count == game->num_enemies){
            printf("Next Wave!\n");
            int wave = game->game_model.get_wave_num();
            if (wave == 2) {
                int level = game->game_model.get_level();
                level++;
                game->game_model.set_level(level);
                game->startLevel();
                game->castle.set_castle_health(20);
            } else {
                wave++;
                game->game_model.set_wave_num(wave);
            }
            //printf("game_model.get_wave_num() = %i\n",game->game_model.get_wave_num());
            for(int i = 0; i < game->num_enemies; i++){
                current_enemies[i] = game->game_model.levels.wave_enemies[wave][i];
            }
        }
    
    //print_array();
        // Update lasttime (reset time)
        lasttime = current_time;
    }
    glutPostRedisplay();
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
    
    glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
    //draw objects
    
    
    //draw_grid();
    
    draw_castle();

    draw_hit(hit);
    
    if (Moat_flag == true) {
        draw_moat();
    }
    
    for(int i = 0; i < current_towers; i++){
        draw_tower(active_towers[i]);
    }
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    draw_current_enemies();
    
    draw_text();
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
    
    if (game->endgame == true && (key == 'n' || key == 'N')) {
        delete game;
        exit(0);
    }
    if (game->endgame == true && (key == 'y' || key == 'Y')) {
        // Start new game
        delete game;
        game = new GameController;
        game->game_setup();
        for(int i = 0; i < game->num_enemies; i++){
            current_enemies[i] = game->game_model.levels.wave_enemies[0][i];
        }
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
        printf("Mouse func x, y: %f, %f\n", start_x*dt, start_y*dt);
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
    
    // Redraw screen
    glutPostRedisplay();
}

// Draw Current Enemies
void GameView::draw_current_enemies(){
    for(int i = 0; i < game->num_enemies; i++){
        if(current_enemies[i].visible){
            draw_zombie(current_enemies[i]);
        }
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
    int resources = game->game_model.get_num_resources();
    // Tower Selected
    if ((id == add_tower) && (current_towers <= tower_max)) {
        if (resources >= upgrades.tower_cost) {
            // Create new tower
            TowerModel new_tower;
            printf("Tower x y: %f, %f\n", start_x*dt, start_y*dt);
            new_tower.x = start_x*dt;
            new_tower.y = start_y*dt;
            // Add new tower to array
            active_towers[current_towers] = new_tower;
            // increment current number of towers
            current_towers++;
            grid_location[new_tower.y][new_tower.x] = 8;
            
            // decrease resources
            resources = resources - upgrades.tower_cost;
            game->game_model.set_num_resources(resources);
        }
    // Health increased
    } else if (id == castle_health_increase) {
        if (resources >= upgrades.castle_health_upgrade_cost) {
            int health = game->castle.get_castle_health();
            health = health + upgrades.castle_health_upgrade;
            game->castle.set_castle_health(health);
            resources = resources - upgrades.castle_health_upgrade_cost;
            game->game_model.set_num_resources(resources);
        }
    // Moat built
    } else if (id == add_moat) {
        if (resources >= upgrades.moat_upgrade_cost) {
            Moat_flag = true;
            resources = resources - upgrades.moat_upgrade_cost;
            game->game_model.set_num_resources(resources);
        }
    }
}

// Routine to draw text on screen
void GameView::draw_text() {
    glPushMatrix();
    glLoadIdentity();
    
    // Create strings
    sprintf(healthStr,"Castle Health:  %d",game->castle.get_castle_health());
    sprintf(resourcesStr,"Resources:  %d",game->game_model.get_num_resources());
    sprintf(pointsStr,"Total Points:  %d",game->game_model.get_total_points());
    sprintf(levelStr,"Level:  %d",game->game_model.get_level()+1);
    sprintf(waveStr,"Wave:  %d",game->game_model.get_wave_num()+1);
    sprintf(waveStr,"Wave:  %d",game->game_model.get_wave_num()+1);
    glColor3f(0.0f,0.0f,1.0f);
    // Set the text to the top left corner
    glRasterPos2f(-18.0f,17.0f);
    for (unsigned int i = 0; i<strlen(healthStr); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, healthStr[i]);
    }
    glRasterPos2f(-18.0f,16.0f);
    for (unsigned int i = 0; i<strlen(resourcesStr); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, resourcesStr[i]);
    }
    glRasterPos2f(-18.0f,15.0f);
    for (unsigned int i = 0; i<strlen(pointsStr); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, pointsStr[i]);
    }
    glRasterPos2f(15.0f,17.0f);
    for (unsigned int i = 0; i<strlen(levelStr); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, levelStr[i]);
    }
    glRasterPos2f(15.0f,16.0f);
    for (unsigned int i = 0; i<strlen(waveStr); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, waveStr[i]);
    }
    
    
    if (game->endgame == true) {
        glColor3f(0.0f,1.0f,0.0f);
        sprintf(gameoverStr,"GAME OVER");
        glRasterPos2f(-3.0f,2.0f);
        for (unsigned int i = 0; i<strlen(gameoverStr); i++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, gameoverStr[i]);
        }
        sprintf(continueStr,"CONTINUE?");
        glRasterPos2f(-3.0f,-1.0f);
        for (unsigned int i = 0; i<strlen(continueStr); i++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, continueStr[i]);
        }
        sprintf(yesnoStr,"     Y         N");
        glRasterPos2f(-3.0f,-3.0f);
        for (unsigned int i = 0; i<strlen(yesnoStr); i++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, yesnoStr[i]);
        }
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
        glTranslatef(zombie.x-20, zombie.y-20, 0.0f);
        glColor3f(0.8f, 0.2f, 0.2f);
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

// Draw tower method
void GameView::draw_tower(TowerModel tower) {
    tower_quadric = gluNewQuadric();
    gluQuadricDrawStyle(tower_quadric, GLU_FILL);
    gluQuadricNormals(tower_quadric, GLU_SMOOTH);
    
    glPushAttrib(GL_CURRENT_BIT);
    glPushMatrix();
        //glTranslatef(4, -4, 0.0f);
        glTranslatef(-(tower.x-20),tower.y-20, 0.0f);
        glColor3f(0.75f, 0.75f, 0.75f);
        //glScalef(0.03, 0.03, 1);
        gluDisk(tower_quadric, 0, 1.5, 100, 100);
        glColor3f(0.0f, 0.0f, 0.0f);
        gluDisk(tower_quadric, 1.4, 1.5, 100, 100);
        // Firing Range
        glColor3f(1.0f, 0.0f, 0.0f);
        gluDisk(tower_quadric, 4.95, 5.0, 100, 100);
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
        for(int i = 0; i < current_towers; i++){
            draw_tower(active_towers[i]);
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
    for(int i = 0; i < game->num_enemies; i++){
        draw_zombie(game->game_model.levels.wave_enemies[wave_num][i]);
    }
    for(int i = 0; i < game->num_enemies; i++){
        //game.game_model.levels.wave_enemies[wave_num][i].step();
    }
    
}
// Print Out arrary
void GameView::print_array(){
    for(int i = 0; i < 40; i++){
        for(int j = 0; j < 40; j++){
            if(grid_location[i][j] == 9){
                printf(" |");
            } else if(grid_location[i][j] == 8){
                printf("O");
            }else if(grid_location[i][j] == 7){
                printf("X");
            }else{
                printf(" _");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void GameView::draw_moat() {
        glPushAttrib(GL_CURRENT_BIT);
        glPushMatrix();
        glColor3f(0.0f, 0.0f, 0.75f);
        glBegin(GL_POLYGON);
            // Counter-ClockWise around origin
            // Top Left
            glVertex3f(-6.0f, 6.0f, 0.0f);
            glVertex3f(-6.0f, -6.0f, 0.0f);
            glVertex3f(6.0f, -6.0f, 0.0f);
            glVertex3f(6.0f, 6.0f, 0.0f);
        glEnd();
        glColor3f(0.0f, 0.0f, 0.0f);
        // Do not fill polygon
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_POLYGON);
            // Top Left
            glVertex3f(-6.0f, 6.0f, 0.0f);
            glVertex3f(-6.0f, -6.0f, 0.0f);
            glVertex3f(-6.0f, -6.0f, 0.0f);
            glVertex3f(-6.0f, 6.0f, 0.0f);
        glEnd();
    
        // Revert Changes
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glPopMatrix();
        glPopAttrib();
    
        glPushAttrib(GL_CURRENT_BIT);
        glPushMatrix();
        glColor3f(0.5f,0.5f,0.25f);
        glBegin(GL_POLYGON);
        // Counter-ClockWise around origin
        // Top Left
        glVertex3f(-1.0f, -5.0f, 0.0f);
        glVertex3f(-1.0f, -7.0f, 0.0f);
        glVertex3f(1.0f, -7.0f, 0.0f);
        glVertex3f(1.0f, -5.0f, 0.0f);
        glEnd();
        glColor3f(0.0f, 0.0f, 0.0f);
        // Do not fill polygon
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_POLYGON);
        // Top Left
        glVertex3f(-1.0f, -5.0f, 0.0f);
        glVertex3f(-1.0f, -7.0f, 0.0f);
        glVertex3f(1.0f, -7.0f, 0.0f);
        glVertex3f(1.0f, -5.0f, 0.0f);
        glEnd();
    
        // Revert Changes
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glPopMatrix();
        glPopAttrib();
    }

// Check area around towers for zombies
void GameView::check_tower_proximity(){
    for(int i = 0; i < current_towers; i++){
        // Get tower location
        // go through zombies
        for(int j = 0; j < game->num_enemies; j++){
            
            if((abs(current_enemies[j].x - active_towers[i].x) <= active_towers[i].range) && (abs(current_enemies[j].y - active_towers[i].y) <= active_towers[i].range)){
                // Shoot the zombie
                
                //printf("Zombie in range! Zombie: %i, %i Tower: %i, %i\n", current_enemies[j].x, current_enemies[j].y, active_towers[i].x, active_towers[i].y);
                grid_location[current_enemies[j].y][current_enemies[j].x] = 7;
                //print_array();
                //TODO: Draw Shovel-Arrow
                //start at tower, end at zombie position
                if(current_enemies[j].health > 0){
                    current_enemies[j].health = current_enemies[j].health - 1;
                    start_hit_x = active_towers[i].x;
                    start_hit_y = active_towers[i].y;
                    end_hit_x = current_enemies[j].x;
                    end_hit_y = current_enemies[j].y;
                    hit = true;
                }
    
                if(current_enemies[j].health <= 0){
                    current_enemies[j].visible = false;
                    current_enemies[j].x = 2000;
                    game->update_total_points();
                    
                }
                //hit = false;
            }
        }

    }
}
void GameView::draw_hit(bool hit){
    //drawing shot
    if(hit == true){
        glPushAttrib(GL_CURRENT_BIT);
            glPushMatrix();
                glLineWidth(2.5);
                glColor3f(1.0, 0.0, 0.0);
                glBegin(GL_LINES);
                    glVertex2f(-(start_hit_x - 20), start_hit_y - 20);
                    glVertex2f(-(end_hit_x - 20),end_hit_y - 20);
                glEnd();
            glPopMatrix();
        glPopAttrib();
        
        printf("start hit in x: %i y: %i\n",start_hit_x, start_hit_y);
        printf("end hit in x: %i y: %i\n",end_hit_x, end_hit_y);
    }else{
        return;
    }
    return;
    
}