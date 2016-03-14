//
//  CastleModel.cpp
//  Zombie Tower Defense
//


#include "CastleModel.hpp"

// Constructor
CastleModel::CastleModel() {
     castle_health = 100;
}

// Destructor
CastleModel::~CastleModel() {
    
}

int CastleModel::get_castle_health() {
    return castle_health;
}

void CastleModel::set_castle_health(int health) {
    this->castle_health = castle_health;
}

void CastleModel::draw(){
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

