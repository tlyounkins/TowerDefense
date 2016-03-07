//
//  ZombieModel.cpp
//  Zombie Tower Defense
//


#include "ZombieModel.hpp"

// Constructor
ZombieModel::ZombieModel() {
  
}

// Destructor
ZombieModel::~ZombieModel() {
    
}

void ZombieModel::draw(){
    printf("Drawing\n");
    this->quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricNormals(quadric, GLU_SMOOTH);
    
    glPushAttrib(GL_CURRENT_BIT);
    glPushMatrix();
        glColor3f(0.2f, 0.8f, 0.2f);
        glScalef(0.01, 0.01, 1);
        gluDisk(quadric, 0, 2, 100, 100);
        glColor3f(0.0f, 0.0f, 0.0f);
        gluDisk(quadric, 1.9, 2, 100, 100);
    glPopMatrix();
    glPopAttrib();
    printf("Done\n");
}