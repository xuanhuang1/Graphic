//
//  objects.h
//  
//
//  Created by Xuan Huang on 9/13/16.
//
//

#ifndef objects_h
#define objects_h

#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>

#endif /* objects_h */

enum{FALSE, TRUE};
enum{LEFTSHOOT,NORMALSHOOT, RIGHTSHOOT};
enum{MissileFromShip, MissileFromAlien};


typedef struct {
    GLdouble centerX;
    GLdouble centerY;
    GLint index;
    GLint ifAlive;
} Alien;

typedef struct Missile{
    GLdouble centerX;
    GLdouble centerY;
    GLdouble transX;
    GLdouble transY;
    GLint ifValid;
    GLint shootAngle;
} Missile;

typedef struct Node{
    Missile* data;
    struct Node* next;
    struct Node* head;
    struct Node* tail;
}Node;


Missile *make_Missile(GLdouble x, GLdouble y,GLdouble tx, GLdouble ty, GLint ang);

Node *makeNode(Missile* p);

void addNode(Node* p, Node** list);
void deleteNode(Node* p, Node** list);
void clearNode(Node** list);


