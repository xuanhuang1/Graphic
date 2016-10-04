#ifndef __FUNC__H

#define __FUNC__H
#include "structs.h"


void addVect(GLfloat *vx1, GLfloat *vy1, GLfloat *vz1, GLfloat vx2, GLfloat vy2, GLfloat vz2);

GLfloat dotProd(GLfloat vx1, GLfloat vy1, GLfloat vz1, GLfloat vx2, GLfloat vy2, GLfloat vz2);
void crossProd(GLfloat a1, GLfloat a2, GLfloat a3, GLfloat b1, GLfloat b2, GLfloat b3, GLfloat * v1, GLfloat * v2, GLfloat * v3);
GLfloat angleBetweenVect(GLfloat vx1, GLfloat vy1, GLfloat vz1, GLfloat vx2, GLfloat vy2, GLfloat vz2);
void normalizeVec(GLfloat *vx1, GLfloat *vy1, GLfloat *vz1);
void normalizeTwoVec(GLfloat *vx1, GLfloat *vy1);
GLfloat twoDAngle(GLfloat x1, GLfloat y1,GLfloat x2, GLfloat y2);

void drawCheckBoard();
void drawCube(Boid b);
void drawBoid(Boid b);
void drawShadow(Boid b);
void updateGoalDirc(Boid *b, GLfloat gv1, GLfloat gv2);
void updateBoidDirc(Boid *b, GLfloat gv1, GLfloat gv2);


void ruleOfBirdsGatherToCentroid(GLfloat radius, Boid* boids, GLfloat *vx, GLfloat *vy, GLfloat *vz, Boid* theBoid, GLint numOfBoids);
void ruleOfBirdsSeperation(Boid* boids, GLfloat *vx, GLfloat *vy, GLfloat *vz, Boid* theBoid, GLint numOfBoids, GLfloat distance);
void ruleOfBirdsVelocityMatch(GLfloat radius, Boid* boids, GLfloat *vx, GLfloat *vy, GLfloat *vz, Boid* theBoid, GLint numOfBoids);


void anotherLookAt(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat,GLfloat *m1, GLfloat *m2,GLfloat *m3,GLfloat *m4,GLfloat *m5,GLfloat *m6, GLfloat *m7, GLfloat *m8,GLfloat *m9,GLfloat *m10,GLfloat *m11,GLfloat *m12,GLfloat *m13, GLfloat *m14,GLfloat *m15,GLfloat *m16);

void anotherPerspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar, GLfloat *m1, GLfloat *m2,GLfloat *m3,GLfloat *m4,GLfloat *m5,GLfloat *m6, GLfloat *m7, GLfloat *m8,GLfloat *m9,GLfloat *m10,GLfloat *m11,GLfloat *m12,GLfloat *m13, GLfloat *m14,GLfloat *m15,GLfloat *m16);
#endif