//
//  GameView.cpp
//  Zombie Tower Defense
//

#include "GameView.hpp"
#define SIZE 500
#define N 3
#define TOWER_MAX 50

#define add_tower 0
#define castle_health_increase 1
#define add_moat 2
#define add_mage_tower 3

GameController *game;
UpgradesModel upgrades;
GLUquadricObj *tower_quadric;

int castle_starting_health;
int enemy_max;
int current_towers = 0;
int current_mage_towers = 0;
int current_powerups = 0;
bool Tower_flag1 = false;
bool Moat_flag = false;
bool hit = false;
bool game_paused = false;
ZombieModel current_enemies[100];
TowerModel active_towers[TOWER_MAX];
TowerModel active_mage_towers[TOWER_MAX];

PowerUpModel power_ups[300];

// power up variable
bool tower_range = false;
bool tower_speed = false;
bool zombie_health = false;
bool zombie_speed = false;
bool multi_shot = false;

bool neg_tower_range = false;
bool neg_tower_speed = false;
bool neg_zombie_health = false;
bool neg_zombie_speed = false;
bool double_castle_damage = false;

int tower_range_timer = 20;
int tower_speed_timer = 20;
int zombie_health_timer = 20;
int zombie_speed_timer = 20;
int multi_shot_timer = 20;

int neg_tower_range_timer = 20;
int neg_tower_speed_timer = 20;
int neg_zombie_health_timer = 20;
int neg_zombie_speed_timer = 20;
int double_castle_timer = 20;

char healthStr[32];
char resourcesStr[32];
char pointsStr[32];
char waveStr[32];
char levelStr[32];
char gameoverStr[32];
char levelcompleteStr[32];
char continueStr[32];
char yesnoStr[32];

// Power up Strings
char towerRangeStr[32];
char towerSpeedStr[32];
char zombieHealthStr[32];
char zombieSpeedStr[32];
char multiShotStr[32];

char negTowerRangeStr[32];
char negTowerSpeedStr[32];
char negZombieHealthStr[32];
char negZombieSpeedStr[32];
char doubleCastleStr[32];

GLfloat start_x = 0.0f;
GLfloat start_y = 0.0f;
GLfloat tower_x = 0.0f;
GLfloat tower_y = 0.0f;
int start_hit_x = 0.0;
int start_hit_y = 0.0;
int end_hit_x = 0.0;
int end_hit_y = 0.0;

// Global animation variables
GLint fps = 10; // Increase to increase movement speed
GLint current_time;
GLint lasttime;

// Conversion from screen to world coordinates
GLfloat dt = 0.04f;

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
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,9,9,9,9,9,9,9,9,9,9,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//16
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,9,9,9,9,9,9,9,9,9,9,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//17
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,9,9,9,9,9,9,9,9,9,9,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//18
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,9,9,9,9,9,9,9,9,9,9,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//19
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,9,9,9,9,9,9,9,9,9,9,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//20
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,9,9,9,9,9,9,9,9,9,9,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//21
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,9,9,9,9,9,9,9,9,9,9,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//22
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,9,9,9,9,9,9,9,9,9,9,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//23
    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,9,9,9,9,9,9,9,9,9,9,0,0,0,0,0,0,0,0,0,0,0,0,0,9},//24
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
    castle_starting_health = game->castle.get_castle_health();
    printf("Initializing castle health to %i\n\n",castle_starting_health);
    
#ifndef OSX
    // Initialize GLEW
    glewInit();
#endif
    
    // Define Callbacks
    glutDisplayFunc(display);
    glutKeyboardFunc(keyFunc);
    glutIdleFunc(idleFunc);
    glutMouseFunc(mousefunc);
    
    // Set Background Color
    glClearColor(0.0f, 0.25f, 0.0f, 1.0f);

    //Temp?
    for (int i = 0; i < game->num_enemies; i++) {
        current_enemies[i] = game->game_model.levels.wave_enemies[0][i];
    }
    
    // Create upgrades men
    glutCreateMenu(upgrades_menu);
    glutAddMenuEntry("Add Tower: 500 resources",add_tower);
    glutAddMenuEntry("Increase Castle Health by 5: 500 resources",castle_health_increase);
    glutAddMenuEntry("Add Moat: 1000 resources",add_moat);
    glutAddMenuEntry("Add Mage Tower: 2000 resources",add_mage_tower);
    
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
    if ((current_time - lasttime > 1000.0f/fps) && !game_paused) {
        int count = 0;
        
        // Move Zombies
        for (int i = 0; i < game->num_enemies; i++) {
            // Check zombie location
            if ((current_enemies[i].x == 20) && (current_enemies[i].y == 25)) {
                // Zombie made it to castle
                current_enemies[i].x = 0;
                current_enemies[i].y = 0;
                current_enemies[i].visible = false;
                
                // Damage Castle
                int health = game->castle.get_castle_health();
                health--;
                printf("Your castle takes damage!\n");
                game->castle.set_castle_health(health);
                printf("Castle health is now %i\n",health);
                
                // End game if health is 0
                if (health <= 0) {
                    printf("\n\n");
                    game->endGame();
                }
            } else {
                // Count how many enemies are out of the game
                if (((current_enemies[i].x == 0) && (current_enemies[i].y == 0)) || (!current_enemies[i].visible)) {
                    count++;
                }
                // Remaining enemies take a step
                else if (game->endgame == false) {
                    current_enemies[i].step(grid_location);
                }
            }
            // Check for powerup collision
            for(int j = 0;  j < current_powerups; j++){
                if((current_enemies[i].x == power_ups[j].x) && (current_enemies[i].y == power_ups[j].y)){
                    apply_powerup(false);
                    // "Remove" power up
                    power_ups[j].x = 100;
                    power_ups[j].y = 100;
                }
            }
        }
       
        // Next Wave
        if (count == game->num_enemies) {
            printf("Next Wave!\n");
            
            int wave = game->game_model.get_wave_num();
            // Increase level if last wave
            if (wave == 9) {
                game_paused = !game_paused;
                game->levelcomplete = true;
                // Loop back around
                if(game->game_model.current_level == 9){
                    game->game_model.current_level = -1;
                }
                
            }
            // Go to next wave instead
            else {
                wave++;
                game->game_model.set_wave_num(wave);
                // Add wave enemies to current enemies
                for (int i = 0; i < game->num_enemies; i++) {
                    current_enemies[i] = game->game_model.levels.wave_enemies[wave][i];
                    if(zombie_health){
                        current_enemies[i].health = 1;
                    }
                    if(zombie_speed){
                        current_enemies[i].speed += 2;
                    }
                }
            }
            //printf("game_model.get_wave_num() = %i\n",game->game_model.get_wave_num());
            
            
        }
        
        // Pew Pew
        check_tower_proximity();
        check_mage_tower_proximity();
    
        //print_array();
        
        // Check powerups, cancel if timer done
        // Tower Range Buff
        if(tower_range){
            if(tower_range_timer != 0){
                tower_range_timer--;
            } else{
                tower_range = false;
                
                // Reset tower range
                for(int i = 0; i < current_towers; i++){
                    active_towers[i].range = active_towers[i].range - 5;
                }
                
                // Reset mage tower range
                for(int i = 0; i < current_towers; i++){
                    active_mage_towers[i].range = active_mage_towers[i].range - 5;
                }
                // Reset timer
                tower_range_timer = 20;
            }
        }
        // Caffinated Archers Buff
        if(tower_speed){
            if(tower_speed_timer != 0){
                tower_speed_timer--;
            } else{
                tower_speed = false;
                
                // Reset tower speed
                for(int i = 0; i < current_towers; i++){
                    active_towers[i].speed = active_towers[i].speed - 5;
                }
                
                // Reset mage tower speed
                for(int i = 0; i < current_mage_towers; i++){
                    active_mage_towers[i].speed = active_mage_towers[i].speed - 5;
                }

                
                // Reset Timer
                tower_speed_timer = 20;
            }
        }
        // Zombie Speed Buff
        if(zombie_speed){
            if(zombie_speed_timer != 0){
                zombie_speed_timer--;
            } else{
                zombie_speed = false;
                
                // Reset Zombie Speed
                for(int i = 0; i < game->num_enemies; i++){
                    current_enemies[i].speed -= 2;
                }
                
                // Reset Timer
                zombie_speed_timer = 20;
            }
        }
        // Zombie Health Buff
        if(zombie_health){
            if(zombie_health_timer != 0){
                zombie_health_timer--;
            } else{
                zombie_health = false;
                
                // Reset Health
                for(int i = 0; i < game->num_enemies; i++){
                    current_enemies[i].health = 4;
                }
                
                // Reset Timer
                zombie_speed_timer = 20;
            }
        }
        // Multishot
        if(multi_shot){
            if(multi_shot_timer != 0){
                multi_shot_timer--;
            } else{
                multi_shot = false;
                
                multi_shot_timer = 20;
            }
        }
        // Tower Range debuff
        if(neg_tower_range){
            if(neg_tower_range_timer != 0){
                neg_tower_range_timer--;
            } else{
                neg_tower_range = false;
                
                // Reset tower range
                for(int i = 0; i < current_towers; i++){
                    active_towers[i].range += 2;
                }
                
                // Reset mage tower range
                for(int i = 0; i < current_towers; i++){
                    active_mage_towers[i].range += 1;
                }
                
                neg_tower_range_timer = 20;
            }
        }
        // Caffine Deprived Archers
        if(neg_tower_speed){
            if(neg_tower_speed_timer != 0){
                neg_tower_speed_timer--;
            } else{
                neg_tower_speed = false;
                
                // Reset tower speed
                for(int i = 0; i < current_towers; i++){
                    active_towers[i].speed += 5;
                }
                
                // Reset mage tower speed
                for(int i = 0; i < current_mage_towers; i++){
                    active_mage_towers[i].speed += 5;
                }
                
                
                // Reset Timer
                neg_tower_speed_timer = 20;
            }
        }
        // Zombie Speed Debuff
        if(neg_zombie_speed){
            if(neg_zombie_speed_timer != 0){
                neg_zombie_speed_timer--;
            } else{
                neg_zombie_speed = false;
                
                // Reset Zombie Speed
                for(int i = 0; i < game->num_enemies; i++){
                    current_enemies[i].speed += 2;
                }
                
                // Reset Timer
                neg_zombie_speed_timer = 20;
            }
        }
        // Zombie Health Debuff
        if(neg_zombie_health){
            if(neg_zombie_health_timer != 0){
                neg_zombie_health_timer--;
            } else{
                neg_zombie_health = false;
                
                // Reset Health
                for(int i = 0; i < game->num_enemies; i++){
                    current_enemies[i].health -= 2;
                }
                
                // Reset Timer
                neg_zombie_speed_timer = 20;
            }
        }
        // Double Castle Damage
        if(double_castle_damage){
            if(double_castle_timer != 0){
                double_castle_timer--;
            } else {
                double_castle_damage = false;
                
                // Reset Timer
                double_castle_timer = 20;
            }
        }

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
    
    draw_grid();

    if (Moat_flag == true) {
        draw_moat();
    }
    
    draw_castle();
    
    // Draw active towers
    for (int i = 0; i < current_towers; i++) {
        draw_tower(active_towers[i]);
    }
    
    // Draw active mage towers
    for (int i = 0; i < current_mage_towers; i++) {
        draw_mage_tower(active_mage_towers[i]);
    }
    
    // Draw power ups
    for(int i = 0; i < current_powerups; i++){
        draw_powerup(power_ups[i]);
    }
    
    // Draw shots per tower
    for (int i = 0; i < current_towers; i++) {
        if (active_towers[i].hit){
            active_towers[i].draw_hit();
            
        }
    }
    
    // Draw shots per mage tower
    for (int i = 0; i < current_mage_towers; i++) {
        if (active_mage_towers[i].hit){
            active_mage_towers[i].draw_hit();
            
        }
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
    if (key == ' ') {
        game_paused = !game_paused;
    }
    
    if (game->levelcomplete == true && (key == 'y' || key == 'Y')) {
        int level = game->game_model.get_level();
        level++;
        game->game_model.set_level(level);
        game->startLevel();
        game->castle.set_castle_health(castle_starting_health);
        game->levelcomplete = false;
        game_paused = !game_paused;
        current_powerups = 0;
        // Add wave enemies to current enemies
        int wave = 0;
        for (int i = 0; i < game->num_enemies; i++) {
            current_enemies[i] = game->game_model.levels.wave_enemies[wave][i];
        }
    }
    if (game->levelcomplete == true && (key == 'n' || key == 'N')) {
        game->endgame = true;
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
        castle_starting_health = game->castle.get_castle_health();
        printf("Initializing castle health to %i\n\n",castle_starting_health);
        for (int i = 0; i < game->num_enemies; i++) {
            current_enemies[i] = game->game_model.levels.wave_enemies[0][i];
        }
    }
}

// Mouse click callback
void GameView::mousefunc(int button, int state, int x, int y) {
    
    // Store cursor position when left button is clicked
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        start_x = x;
        start_y = y;
        printf("Mouse func x, y: %f, %f\n", start_x*dt, start_y*dt);
        
        // Check if mouse clicked on powerup
        for(int i = 0; i < current_powerups; i++){
            //printf("X: %i Y: %i \n", power_ups[i].x, power_ups[i].y);
            if((floor(x*dt) == power_ups[i].x) && (floor(y*dt) == power_ups[i].y)){
                //for testing
                //printf("Poke\n");
                apply_powerup(true);
                power_ups[i].x = 100;
                power_ups[i].y = 100;
            }
        }
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
        start_x = x;
        start_y = y;
        printf("Mouse func x, y: %f, %f\n", start_x*dt, start_y*dt);
    }
    glutPostRedisplay();
}

// Draw Current Enemies
void GameView::draw_current_enemies() {
    for (int i = 0; i < game->num_enemies; i++) {
        if (current_enemies[i].visible) {
            draw_zombie(current_enemies[i]);
        }
    }
}

// Draw Grid
void GameView::draw_grid() {
    for (int i = -20; i <= 20; i++) {
        // Draw Vertical Lines
        glPushAttrib(GL_CURRENT_BIT);
        glPushMatrix();
            if (i == 0) {
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
            if (j == 0) {
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
    if ((id == add_tower) && (current_towers <= TOWER_MAX)) {
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
    // Mage Tower
    } else if((id == add_mage_tower) && (current_mage_towers <= TOWER_MAX)){
        if(resources >= upgrades.mage_tower_cost){
            //creates new mage tower
            TowerModel new_mage_tower;
            printf("Mage Tower x y: %f, %f\n", start_x*dt, start_y*dt);
            new_mage_tower.x = start_x*dt;
            new_mage_tower.y = start_y*dt;
            new_mage_tower.range = 3;
            new_mage_tower.speed = 5;
            //adds mage tower to active tower array
            active_mage_towers[current_mage_towers] = new_mage_tower;
            // increment current number of towers
            current_mage_towers++;
            grid_location[new_mage_tower.y][new_mage_tower.x] = 8;
            
            // decrease resources
            resources = resources - upgrades.mage_tower_cost;
            game->game_model.set_num_resources(resources);
        }
        
     // Health increased
    }else if (id == castle_health_increase) {
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
    // Powerup Strings
    sprintf(towerRangeStr,"Tower Range: %d", tower_range_timer);
    sprintf(towerSpeedStr, "Tower Speed: %d", tower_speed_timer);
    sprintf(zombieHealthStr, "Zombie HP: %d", zombie_health_timer);
    sprintf(zombieSpeedStr, "Zombie Slow: %d", zombie_speed_timer);
    sprintf(multiShotStr, "Multishot: %d", multi_shot_timer);
    sprintf(negTowerRangeStr,"Tower Range: %d", neg_tower_range_timer);
    sprintf(negTowerSpeedStr, "Tower Speed: %d", neg_tower_speed_timer);
    sprintf(negZombieHealthStr, "Zombie HP: %d", neg_zombie_health_timer);
    sprintf(negZombieSpeedStr, "Zombie Slow: %d", neg_zombie_speed_timer);
    sprintf(doubleCastleStr, "Double Damage: %d", double_castle_timer);
    glColor3f(1.0f,1.0f,1.0f);
    
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
    
    // Set Power Up Text to Bottom Left Corner
    // Positive
    if(tower_range){
        glRasterPos2f(-19.0f, -18.0f);
        for(unsigned int i = 0; i < strlen(towerRangeStr); i++){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, towerRangeStr[i]);
        }
    }
    if(tower_speed){
        glRasterPos2f(-11.0f, -18.0f);
        for(unsigned int i = 0; i < strlen(towerSpeedStr); i++){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, towerSpeedStr[i]);
        }
    }
    if(zombie_health){
        glRasterPos2f(-3.0f, -18.0f);
        for(unsigned int i = 0; i < strlen(zombieHealthStr); i++){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, zombieHealthStr[i]);
        }
    }
    if(zombie_speed){
        glRasterPos2f(5.0f, -18.0f);
        for(unsigned int i = 0; i < strlen(zombieSpeedStr); i++){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, zombieSpeedStr[i]);
        }
    }
    if(multi_shot){
        glRasterPos2f(13.0f, -18.0f);
        for(unsigned int i = 0; i < strlen(multiShotStr); i++){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, multiShotStr[i]);
        }
    }
    // Negative
    glColor3f(1.0f, 0.0f, 0.0f);
    if(neg_tower_range){
        glRasterPos2f(-19.0f, -19.0f);
        for(unsigned int i = 0; i < strlen(negTowerRangeStr); i++){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, negTowerRangeStr[i]);
        }
    }
    if(neg_tower_speed){
        glRasterPos2f(-11.0f, -19.0f);
        for(unsigned int i = 0; i < strlen(negTowerSpeedStr); i++){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, negTowerSpeedStr[i]);
        }
    }
    if(neg_zombie_health){
        glRasterPos2f(-3.0f, -19.0f);
        for(unsigned int i = 0; i < strlen(negZombieHealthStr); i++){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, negZombieHealthStr[i]);
        }
    }
    if(neg_zombie_speed){
        glRasterPos2f(5.0f, -19.0f);
        for(unsigned int i = 0; i < strlen(negZombieSpeedStr); i++){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, negZombieSpeedStr[i]);
        }
    }
    if(double_castle_damage){
        glRasterPos2f(13.0f, -19.0f);
        for(unsigned int i = 0; i < strlen(doubleCastleStr); i++){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, doubleCastleStr[i]);
        }
    }
    
    // Reset Color
    glColor3f(1.0f,1.0f,1.0f);
    
    if (game->endgame == true) {
        glColor3f(1.0f,1.0f,1.0f);
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
    if (game->levelcomplete == true) {
        glColor3f(1.0f,1.0f,1.0f);
        sprintf(gameoverStr,"LEVEL COMPLETE!");
        glRasterPos2f(-4.25f,2.0f);
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

// Draw castle function
void GameView::draw_castle() {
    glPushAttrib(GL_CURRENT_BIT);
    glPushMatrix();
        glColor3f(0.5f, 0.5f, 0.5f);
        glBegin(GL_POLYGON);            // Counter-ClockWise around origin
            // Top Left
            glVertex3f(-5.0f, 5.0f, 0.0f);
            glVertex3f(-5.0f, -5.0f, 0.0f);
            glVertex3f(5.0f, -5.0f, 0.0f);
            glVertex3f(5.0f, 5.0f, 0.0f);
        glEnd();
        glColor3f(0.0f, 0.0f, 0.0f);
        // Door
        glBegin(GL_POLYGON);
            glVertex3f(-1.0f, 5.0f, 0.0f);
            glVertex3f(-1.0f, 4.0f, 0.0f);
            glVertex3f(1.0f, 4.0f, 0.0f);
            glVertex3f(1.0f, 5.0f, 0.0f);
        glEnd();
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
        glColor3f(0.5f, 0.5f, 0.5f);
        //glScalef(0.03, 0.03, 1);
        gluDisk(tower_quadric, 0, 1.5, 100, 100);
        glColor3f(0.0f, 0.0f, 0.0f);
        gluDisk(tower_quadric, 1.4, 1.5, 100, 100);
        //Firing Range
        glColor3f(1.0f, 0.0f, 0.0f);
        gluDisk(tower_quadric, tower.range - 0.05, tower.range, 100, 100);
    glPopMatrix();
    glPopAttrib();
}

//Draw mage tower
void GameView::draw_mage_tower(TowerModel mage_tower){
    tower_quadric = gluNewQuadric();
    gluQuadricDrawStyle(tower_quadric, GLU_FILL);
    gluQuadricNormals(tower_quadric, GLU_SMOOTH);

    glPushAttrib(GL_CURRENT_BIT);
    glPushMatrix();
        //glTranslatef(4, -4, 0.0f);
        glTranslatef(-(mage_tower.x-20),mage_tower.y-20, 0.0f);
        glColor3f(0.2f, 0.2f, 0.2f);
        //glScalef(0.03, 0.03, 1);
        gluDisk(tower_quadric, 0, 1.5, 100, 100);
        glColor3f(0.0f, 0.0f, 0.0f);
        gluDisk(tower_quadric, 1.4, 1.5, 100, 100);
        //Firing Range
        glColor3f(1.0f, 0.0f, 1.0f);
        gluDisk(tower_quadric, mage_tower.range - 0.05, mage_tower.range, 100, 100);
    glPopMatrix();
    glPopAttrib();
}
// Start Wave
void GameView::draw_wave(int wave_num, int level) {
    printf("Wave %i starting\n", wave_num);
    for(int i = 0; i < game->num_enemies; i++) {
        draw_zombie(game->game_model.levels.wave_enemies[wave_num][i]);
    }
}

// Print Out arrary
void GameView::print_array() {
    for(int i = 0; i < 40; i++) {
        for(int j = 0; j < 40; j++){
            if(grid_location[i][j] == 9) {
                printf(" |");
            } else if(grid_location[i][j] == 8) {
                printf("O");
            } else if(grid_location[i][j] == 7) {
                printf("X");
            } else {
                printf(" _");
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Draw moat function
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
        glVertex3f(-1.0f, 5.0f, 0.0f);
        glVertex3f(-1.0f, 7.0f, 0.0f);
        glVertex3f(1.0f, 7.0f, 0.0f);
        glVertex3f(1.0f, 5.0f, 0.0f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    // Do not fill polygon
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);
        // Top Left
        glVertex3f(-1.0f, 5.0f, 0.0f);
        glVertex3f(-1.0f, 7.0f, 0.0f);
        glVertex3f(1.0f, 7.0f, 0.0f);
        glVertex3f(1.0f, 5.0f, 0.0f);
    glEnd();
    
    // Revert Changes
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPopMatrix();
    glPopAttrib();
    
    // TODO: Add 9's to map where moat is
}

// Draw Power Up
void GameView::draw_powerup(PowerUpModel powerup){
    tower_quadric = gluNewQuadric();
    gluQuadricDrawStyle(tower_quadric, GLU_FILL);
    gluQuadricNormals(tower_quadric, GLU_SMOOTH);
    
    //printf("Drawing at (%i, %i)\n", zombie.x, zombie.y);
    // Make Random Color
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    
    glPushAttrib(GL_CURRENT_BIT);
    glPushMatrix();
        glTranslatef(-(powerup.x-20), powerup.y-20, 0.0f);
        glColor3f(r, g, b);
        gluDisk(tower_quadric, 0, 0.3, 100, 100);
        glColor3f(0.0f, 0.0f, 0.0f);
        gluDisk(tower_quadric, 0.27, 0.3, 100, 100);
    glPopMatrix();
    glPopAttrib();

}

// Check area around towers for zombies
void GameView::check_tower_proximity() {
    for(int i = 0; i < current_towers; i++) {
        // Get tower location
        // go through zombies
        
        // For Multishot power up
        int shot_count = 0;
        
        // Increase timer on towers
        active_towers[i].cooldown += 2;
        for(int j = 0; j < game->num_enemies; j++){
            
            // Check where zombie is on map
            if((abs(current_enemies[j].x - active_towers[i].x) <= active_towers[i].range) && (abs(current_enemies[j].y - active_towers[i].y) <= active_towers[i].range)){
                // For Testing
                //printf("Zombie in range! Zombie: %i, %i Tower: %i, %i\n", current_enemies[j].x, current_enemies[j].y, active_towers[i].x, active_towers[i].y);
                //print_array();
                
                // Shoot the zombie if cooldown is up
                if(active_towers[i].cooldown >= active_towers[i].speed){
                    
                    shot_count++;
                    
                    // Mark on map where hit occurs
                    grid_location[current_enemies[j].y][current_enemies[j].x] = 7;
                    
                    // Mark hit location
                    if(!active_towers[i].hit){
                        active_towers[i].enemy_x = current_enemies[j].x;
                        active_towers[i].enemy_y = current_enemies[j].y;
                        active_towers[i].enemy_position = j;
                        active_towers[i].hit = true;
                    }
                
                    // Decrement Zombie Health
                    if(current_enemies[j].health > 0){
                        current_enemies[j].health = current_enemies[j].health - 1;
                 
                    }
                    // If Zombie Dead, Remove It
                    if(current_enemies[j].health <= 0){
                        
                        // Chance to drop power up
                        srand(time(NULL));
                        int ran = rand() % 100;
                        // Drop Power Up
                        if(ran <= 100){
                            //printf("spawning power up!\n");
                            
                            // Spawn Power Up where zombie is
                            PowerUpModel powerup;
                            powerup.x = current_enemies[j].x;
                            powerup.y = current_enemies[j].y;
                            
                            power_ups[current_powerups] = powerup;
                            
                            current_powerups++;
                        }
                        
                        // Remove Zombie
                        current_enemies[j].visible = false;
                        current_enemies[j].x = 0;
                        current_enemies[j].y = 0;
                        
                        // Add points
                        game->update_total_points();
                    } 
                    
                    // Restart cooldown if power up not applied
                    if(!multi_shot) {
                        active_towers[i].cooldown = 0;
                    } else{
                        if(shot_count >= 1){
                            active_towers[i].cooldown = 0;
                        }
                    }
                    glutPostRedisplay();
                }
                
                // Tower can only hit one at a time unless poweruped
                if(!multi_shot){
                    break;
                } else{
                    if(shot_count >= 1){
                        break;
                    }
                }
            }
        }
    }
}

// Check area around towers for zombies
void GameView::check_mage_tower_proximity() {
    for(int i = 0; i < current_mage_towers; i++) {
        // Get tower location
        // go through zombies
        
        // For Multishot power up
        int shot_count = 0;
        
        // Increase timer on towers
        active_mage_towers[i].cooldown += 2;
        for(int j = 0; j < game->num_enemies; j++){
            
            // Check where zombie is on map
            if((abs(current_enemies[j].x - active_mage_towers[i].x) <= active_mage_towers[i].range) && (abs(current_enemies[j].y - active_mage_towers[i].y) <= active_mage_towers[i].range)){
                // For Testing
                //printf("Zombie in range! Zombie: %i, %i Tower: %i, %i\n", current_enemies[j].x, current_enemies[j].y, active_towers[i].x, active_towers[i].y);
                //print_array();
                
                // Shoot the zombie if cooldown is up
                if(active_mage_towers[i].cooldown >= active_mage_towers[i].speed){
                    
                    shot_count++;
                    
                    // Mark on map where hit occurs
                    grid_location[current_enemies[j].y][current_enemies[j].x] = 7;
                    
                    // Mark hit location
                    if(!active_mage_towers[i].hit){
                        active_mage_towers[i].enemy_x = current_enemies[j].x;
                        active_mage_towers[i].enemy_y = current_enemies[j].y;
                        active_mage_towers[i].enemy_position = j;
                        active_mage_towers[i].hit = true;
                    }
                    
                    // Decrement Zombie Health
                    if(current_enemies[j].health > 0){
                        current_enemies[j].health = current_enemies[j].health - 1;
                        
                    }
                    // If Zombie Dead, Remove It
                    if(current_enemies[j].health <= 0){
                        
                        // Chance to drop power up
                        srand(time(NULL));
                        int ran = rand() % 100;
                        // Drop Power Up
                        if(ran <= 100){
                            
                            // Spawn Power Up where zombie is
                            PowerUpModel powerup;
                            powerup.x = current_enemies[j].x;
                            powerup.y = current_enemies[j].y;
                            
                            power_ups[current_powerups] = powerup;
                            
                            //printf("spawning power up!\n");
                            current_powerups++;
                        }


                        // Remove Zombie
                        current_enemies[j].visible = false;
                        current_enemies[j].x = 0;
                        current_enemies[j].y = 0;
                        
                        // Add points
                        game->update_total_points();
                    }
                    
                    // Restart cooldown if power up not applied
                    if(!multi_shot) {
                        active_mage_towers[i].cooldown = 0;
                    } else{
                        if(shot_count >= 1){
                            active_mage_towers[i].cooldown = 0;
                        }
                    }
                    glutPostRedisplay();
                }
                
                // Tower can only hit one at a time unless poweruped
                if(!multi_shot){
                    break;
                } else{
                    if(shot_count >= 1){
                        break;
                    }
                }
            }
        }
    }
}

// Apply power up
// Effect is random
// Beneficial if player hits it
// Detremental if zombie runs into it
void GameView::apply_powerup(bool user){
    
    // Player gets it
    if(user){
        int ran = rand() % 100;
        
        // Zombies have less health
        if(ran <= 20){
            if(!zombie_health){
                // Apply to all current enemies
                for(int i = 0; i < game->num_enemies; i++){
                    current_enemies[i].health = 1;
                }
                zombie_health = true;
            } else{
                zombie_health_timer += 20;
            }
        }
        // Zombies move slower
        else if(ran <= 40){
            if(!zombie_speed){
                // Apply to all current enemies
                for(int i = 0; i < game->num_enemies; i++){
                    current_enemies[i].speed += 2;
                }
                zombie_speed = true;
            } else{
                zombie_speed_timer += 20;
            }
            //printf("Zombie Speed Applied!\n");
        }
        
        // Tower Range increased
        else if(ran <= 60){
            if(!tower_range){
                // Apply to all active towers
                for(int i = 0; i < current_towers; i++){
                    active_towers[i].range = active_towers[i].range + 5;
                }
                for(int j = 0; j < current_mage_towers; j++){
                    active_mage_towers[j].range = active_mage_towers[j].range + 5;
                }
                tower_range = true;
            } else {
                // Increase timer instead
                tower_range_timer += 20;
            }
            //printf("Tower Range Applied!\n");
        }
        // Tower Speed
        else if(ran <= 80){
            if(!tower_speed){
                // Apply to all active towers
                for(int i = 0; i < current_towers; i++){
                    active_towers[i].speed = active_towers[i].speed - 5;
                }
                for(int j = 0; j < current_mage_towers; j++){
                    active_mage_towers[j].speed = active_mage_towers[j].speed - 5;
                }
                tower_speed = true;
            } else {
                // Increase timer instead
                tower_range_timer += 20;
            }
            //printf("Tower Speed Applied!\n");
        }
        // Tower can shoot multiple times
        else if(ran <= 100){
            if(!multi_shot){
                multi_shot = true;
            } else {
                // Increase timer
                multi_shot_timer += 20;
            }
            //printf("Multi-Shot Applied!\n");
        }
    } else{
        //printf("Zombie got it!\n");
        int ran = rand()%100;
        
        // Zombies have more health
        if(ran <= 20){
            if(!neg_zombie_health){
                // Apply to all current enemies
                for(int i = 0; i < game->num_enemies; i++){
                    current_enemies[i].health += 2;
                }
                neg_zombie_health = true;
            } else{
                neg_zombie_health_timer += 20;
            }
            //printf("Neg Zombie Health Applied!\n");
        }
        // Zombies move faster
        else if(ran <= 40){
            if(!neg_zombie_speed){
                // Apply to all current enemies
                for(int i = 0; i < game->num_enemies; i++){
                    current_enemies[i].speed -= 2;
                }
                neg_zombie_speed = true;
            } else{
                neg_zombie_speed_timer += 20;
            }
            //printf("Neg Zombie Speed Applied!\n");
        }
        // Tower range decreased
        else if(ran <= 60){
            if(!neg_tower_range){
                // Apply to all active towers
                for(int i = 0; i < current_towers; i++){
                    active_towers[i].range -= 2;
                }
                for(int j = 0; j < current_mage_towers; j++){
                    active_mage_towers[j].range -= 1;
                }
                neg_tower_range = true;
            } else {
                // Increase timer instead
                neg_tower_range_timer += 20;
            }
            //printf("Neg Tower Range Applied!\n");
        }
        // Tower Cooldown increased
        else if(ran <= 80){
            if(!neg_tower_speed){
                // Apply to all active towers
                for(int i = 0; i < current_towers; i++){
                    active_towers[i].speed += 5;
                }
                for(int j = 0; j < current_mage_towers; j++){
                    active_mage_towers[j].speed += 5;
                }
                neg_tower_speed = true;
            } else {
                // Increase timer instead
                neg_tower_range_timer += 20;
            }
            //printf("Neg Tower Speed Applied!\n");
        }
        // Zombies deal double damage
        else{
            if(!double_castle_damage){
                double_castle_damage = true;
            } else {
                double_castle_timer += 20;
            }
        }
    }
}
