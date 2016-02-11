//
//  Main.cpp
//  Zombie Tower Defense
//
//  Created by Tyler Younkins on 2/8/16.
//
//

#include "Main.hpp"
#ifdef OSX
    #include <GLUT/glut.h>
#else
    #include <GL/glew.h>
    #include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>

// Function Prototypes
void display();

int main(int argc, char *argv[]){
    // Initialize GLUT
    glutInit(&argc, argv);
    
    // Initialize the window with double buffering and RGB colors
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    // Set window size
    glutInitWindowSize(512, 512);
    
    // Create WIndow
    glutCreateWindow("Tower Defense");
    
#ifndef OSX
    // Initialize GLEW
    glewInit();
#endif
    
    // Define Callbacks
    glutDisplayFunc(display);
    
    // Set Background Color
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    // Begin event loop
    glutMainLoop();
    return 0;
}

// Display Callback
void display(){
    // Flush Buffer
    glFlush();
    
    // Swap Buffers
    glutSwapBuffers();
}