//
//  ZombieModel.cpp
//  Zombie Tower Defense
//


#include "ZombieModel.hpp"

// Constructor
ZombieModel::ZombieModel() {
    this->x = 0.0;
    this->y = 0.0;
}

// Destructor
ZombieModel::~ZombieModel() {
    
}

void ZombieModel::draw(){
    this->quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricNormals(quadric, GLU_SMOOTH);
    
    
    glPushAttrib(GL_CURRENT_BIT);
    glPushMatrix();
        glTranslatef(this->x, this->y, 0.0f);
        glColor3f(0.2f, 0.8f, 0.2f);
        glScalef(0.01, 0.01, 1);
        gluDisk(quadric, 0, 2, 100, 100);
        glColor3f(0.0f, 0.0f, 0.0f);
        gluDisk(quadric, 1.9, 2, 100, 100);
    glPopMatrix();
    glPopAttrib();
}

void ZombieModel::step(){
    // Head towards (0, -0.25)
    float x = this->get_x_location();
    float y = this->get_y_location();
    
    int ran = rand() % 10;
    if(ran < 5){
        if(x > 0){
            x -= 0.001;
        } else if(x < 0){
            x += 0.001;
        }
    } else{
        if(y > -0.25){
            y -= 0.001;
        } else if(y < -0.25){
            y += 0.001;
        }
    }
    this->x = x;
    this->y = y;
    
    printf("%f %f \n", this->x, this->y);
    
    glutPostRedisplay();
}