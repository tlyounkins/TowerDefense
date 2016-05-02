//
//  TowerModel.cpp
//  Zombie Tower Defense
//
//  Created by Michael Fioravanti on 4/10/16.
//
//

#include "TowerModel.hpp"

// Constructor
TowerModel::TowerModel() {
    range = 5;
    speed = 0;
    cooldown = 1;
    hit = false;
}

// Destructor
TowerModel::~TowerModel() {
    
}


// Draw Hit
void TowerModel::draw_hit(){
    if((this->enemy_x != 0) && (this->enemy_y != 0)){
        glPushAttrib(GL_CURRENT_BIT);
        glPushMatrix();
            //glLineWidth(2.5);
            glColor3f(1.0, 0.75, 0.5);
            glBegin(GL_LINES);
                glVertex2f(-(this->x - 20), this->y - 20);
                glVertex2f(-(this->enemy_x - 20),this->enemy_y - 20);
            glEnd();
        glPopMatrix();
        glPopAttrib();
    }
    
    this->hit = false;
    //printf("start hit in x: %i y: %i\n",x, y);
    //printf("end hit in x: %i y: %i\n",enemy_x, enemy_y);
}