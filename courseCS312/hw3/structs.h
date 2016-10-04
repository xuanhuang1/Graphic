

#ifndef STRUCTS_H
#define STRUCTS_H

#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    GLfloat x1;
    GLfloat y1;
    GLfloat z1;
    GLfloat x2;
    GLfloat y2;
    GLfloat z2;
    GLfloat x3;
    GLfloat y3;
    GLfloat z3;
    GLfloat x4;
    GLfloat y4;
    GLfloat z4;
    GLfloat transx;
    GLfloat transy;
    GLfloat transz;
    GLfloat lastX1;
    GLfloat lastY1;
    GLfloat lastZ1;
    GLfloat currentVx;
    GLfloat currentVy;
    GLfloat currentVz;
} Boid;

#endif


