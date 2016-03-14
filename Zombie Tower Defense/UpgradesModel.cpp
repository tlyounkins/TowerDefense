//
//  UpgradesModel.cpp
//  Zombie Tower Defense
//


#include "UpgradesModel.hpp"

// Constructor
UpgradesModel::UpgradesModel() {
    
}

// Destructor
UpgradesModel::~UpgradesModel() {
    
}

void UpgradesModel::draw_tower() {
    this->tower = gluNewQuadric();
    gluQuadricDrawStyle(tower, GLU_FILL);
    gluQuadricNormals(tower, GLU_SMOOTH);
    
    
    glPushAttrib(GL_CURRENT_BIT);
    glPushMatrix();
        glTranslatef(0.25, -0.25, 0.0f);
        glColor3f(0.75f, 0.75f, 0.75f);
        glScalef(0.03, 0.03, 1);
        gluDisk(tower, 0, 2, 100, 100);
        glColor3f(0.0f, 0.0f, 0.0f);
        gluDisk(tower, 1.9, 2, 100, 100);
    glPopMatrix();
    glPopAttrib();
}