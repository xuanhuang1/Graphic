/*************************************************************************
 functions
 *************************************************************************/

#include "func.h"

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define GRIDCOLNUM 10
#define GRIDLENGTH .1

#define VIEWSIZE 2

void addVect(GLfloat *vx1, GLfloat *vy1, GLfloat *vz1, GLfloat vx2, GLfloat vy2, GLfloat vz2){
    *vx1 = *vx1 + vx2;
    *vy1 = *vy1 + vy2;
    *vz1 = *vz1 + vz2;
}


GLfloat dotProd(GLfloat vx1, GLfloat vy1, GLfloat vz1, GLfloat vx2, GLfloat vy2, GLfloat vz2){
    return vx1*vx2+vy1*vy2+vz1*vz2;
}

void crossProd(GLfloat a1, GLfloat a2, GLfloat a3, GLfloat b1, GLfloat b2, GLfloat b3, GLfloat * v1, GLfloat * v2, GLfloat * v3){
    *v1 = a2*b3 - a3*b2;
    *v2 = a3*b1 - a1*b3;
    *v3 = a1*b2 - a2*b1;
}

GLfloat angleBetweenVect(GLfloat vx1, GLfloat vy1, GLfloat vz1, GLfloat vx2, GLfloat vy2, GLfloat vz2){
    
    GLfloat a =sqrt(pow(vx1,2)+pow(vy1,2)+pow(vz1,2));
    GLfloat b =sqrt(pow(vx2,2)+pow(vy2,2)+pow(vz2,2));
    GLfloat c = vx1*vx2+vy1*vy2+vz1*vz2;
    GLfloat result = c/(a*b);
    
    
    return acos(result);
    
}

void normalizeVec(GLfloat *vx, GLfloat *vy, GLfloat *vz){
    GLfloat a = *vx, b = *vy, c = *vz;
    if (a != 0 || b!= 0 || c!= 0) {
        *vx = a/sqrt(pow(a,2)+pow(b,2)+pow(c,2));
        *vy = b/sqrt(pow(a,2)+pow(b,2)+pow(c,2));
        *vz = c/sqrt(pow(a,2)+pow(b,2)+pow(c,2));
    }
}

void normalizeTwoVec(GLfloat *vx, GLfloat *vy){
    GLfloat a = *vx, b = *vy;
    if (a != 0 || b!= 0) {
        *vx = a/sqrt(pow(a,2)+pow(b,2));
        *vy = b/sqrt(pow(a,2)+pow(b,2));
    }
}

GLfloat twoDAngle(GLfloat x1, GLfloat y1,GLfloat x2, GLfloat y2){
    return atan2((x1*y2-y1*x2), (x1*x2+y1*y2));
}


void drawCheckBoard(){
    
    GLfloat verticesGrid[][3] =
    {{-2,-2,0},{-1.8,-2,0},
        {-1.8,-1.8,0},{-2,-1.8,0}};
    GLfloat colorsGrid[][3] = {{.5, .5, .5},{.5, .5, .5},{.5, .5, .5},{.5, .5, .5}};
    GLubyte quadIndices[4] = {0,1,2,3};
    
    for(int i = 0; i< GRIDCOLNUM*GRIDCOLNUM; i++){
        verticesGrid[0][0] = -(GRIDCOLNUM*GRIDLENGTH) + 2*GRIDLENGTH*(i%GRIDCOLNUM);
        verticesGrid[0][1] = -(GRIDCOLNUM*GRIDLENGTH) + 2*GRIDLENGTH*(i/GRIDCOLNUM);
        verticesGrid[1][0] = -(GRIDCOLNUM*GRIDLENGTH)+GRIDLENGTH + 2*GRIDLENGTH*(i%GRIDCOLNUM);
        verticesGrid[1][1] = -(GRIDCOLNUM*GRIDLENGTH) + 2*GRIDLENGTH*(i/GRIDCOLNUM);
        verticesGrid[2][0] = -(GRIDCOLNUM*GRIDLENGTH)+GRIDLENGTH + 2*GRIDLENGTH*(i%GRIDCOLNUM);
        verticesGrid[2][1] = -(GRIDCOLNUM*GRIDLENGTH)+GRIDLENGTH + 2*GRIDLENGTH*(i/GRIDCOLNUM);
        verticesGrid[3][0] = -(GRIDCOLNUM*GRIDLENGTH) + 2*GRIDLENGTH*(i%GRIDCOLNUM);
        verticesGrid[3][1] = -(GRIDCOLNUM*GRIDLENGTH)+GRIDLENGTH + 2*GRIDLENGTH*(i/GRIDCOLNUM);
        
        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        
        glVertexPointer(3, GL_FLOAT, 0, verticesGrid);
        glColorPointer(3, GL_FLOAT, 0, colorsGrid);
        
        glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, quadIndices);
        
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
    
    for(int i = 0; i< (GRIDCOLNUM-1)*(-1+GRIDCOLNUM); i++){
        verticesGrid[0][0] =GRIDLENGTH -(GRIDCOLNUM*GRIDLENGTH) + 2*GRIDLENGTH*(i%(GRIDCOLNUM-1));
        verticesGrid[0][1] =GRIDLENGTH -(GRIDCOLNUM*GRIDLENGTH) + 2*GRIDLENGTH*(i/(GRIDCOLNUM-1));
        verticesGrid[1][0] =GRIDLENGTH -(GRIDCOLNUM*GRIDLENGTH)+GRIDLENGTH + 2*GRIDLENGTH*(i%(GRIDCOLNUM-1));
        verticesGrid[1][1] =GRIDLENGTH -(GRIDCOLNUM*GRIDLENGTH) + 2*GRIDLENGTH*(i/(GRIDCOLNUM-1));
        verticesGrid[2][0] =GRIDLENGTH -(GRIDCOLNUM*GRIDLENGTH)+GRIDLENGTH + 2*GRIDLENGTH*(i%(GRIDCOLNUM-1));
        verticesGrid[2][1] =GRIDLENGTH -(GRIDCOLNUM*GRIDLENGTH)+GRIDLENGTH + 2*GRIDLENGTH*(i/(GRIDCOLNUM-1));
        verticesGrid[3][0] =GRIDLENGTH -(GRIDCOLNUM*GRIDLENGTH) + 2*GRIDLENGTH*(i%(GRIDCOLNUM-1));
        verticesGrid[3][1] =GRIDLENGTH -(GRIDCOLNUM*GRIDLENGTH)+GRIDLENGTH + 2*GRIDLENGTH*(i/(GRIDCOLNUM-1));
        
        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        
        glVertexPointer(3, GL_FLOAT, 0, verticesGrid);
        glColorPointer(3, GL_FLOAT, 0, colorsGrid);
        
        glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, quadIndices);
        
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
}

void drawCube(Boid b){
    
    glShadeModel(GL_SMOOTH);
    GLfloat vertices[][3] =
    {{b.x1,b.y1,b.z1},{b.x2,b.y2,b.z2},
        {b.x3,b.y3,b.z3},{b.x4,b.y4,b.z4}};
    GLfloat colors[][3] =
    {{0, 0, 0},{1,1,1},
        {1,1,1}, {1,1,1}};
    
    
    GLubyte indices[12] = {0,1,2,0,2,3,0,2,1,0,3,2};
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, indices);
    
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void drawBoid(Boid b){
    glShadeModel(GL_SMOOTH);
    GLfloat vertices[][3] =
    {{b.x1,b.y1,b.z1},{b.x2,b.y2,b.z2},
        {b.x3,b.y3,b.z3},{b.x4,b.y4,b.z4}};
    GLfloat colors[][3] =
    {{0, 0, 0},{1,0,0},
        {1,1,0}, {1,0,0}};
    
    
    GLubyte indices[12] = {0,1,2,0,2,3,0,2,1,0,3,2};
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, indices);
    
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

//shadow


void drawShadow(Boid b){
    glShadeModel(GL_SMOOTH);
    GLfloat vertices2[][3] =
    {{b.x1,b.y1,0.001},{b.x2,b.y2,0.001},
        {b.x3,b.y3,0.001},{b.x4,b.y4,0.001}};
    GLfloat colors2[][3] =
    {{0.2, 0.2, 0.2},{0.2, 0.2, 0.2},
        {0.2, 0.2, 0.2}, {0.2, 0.2, 0.2}};
    
    
    GLubyte indices2[12] = {0,1,2,0,2,3,0,2,1,0,3,2};
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    glVertexPointer(3, GL_FLOAT, 0, vertices2);
    glColorPointer(3, GL_FLOAT, 0, colors2);
    
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, indices2);
    
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void ruleOfBirdsGatherToCentroid(GLfloat radius, Boid* boids, GLfloat *vx, GLfloat *vy, GLfloat *vz, Boid* theBoid, GLint numOfBoids){
    GLfloat sumX = 0, sumY =0, sumZ = 0;
    GLint numOfNeignbors = 0;
    for (int i =0; i < numOfBoids; i++) {
        if (boids+i != theBoid) {
            if(sqrt( pow((boids+i)->transx - theBoid->transx,2) +pow((boids+i)->transy - theBoid->transy,2) +pow((boids+i)->transz - theBoid->transz,2)) < radius){
                sumX+= (boids+i)->transx;
                sumY+= (boids+i)->transy;
                sumZ+= (boids+i)->transz;
                numOfNeignbors ++;
            }
        }
    }
    
    if (numOfNeignbors > 1) {
        sumX = sumX/(numOfNeignbors);
        sumY = sumY/(numOfNeignbors);
        sumZ = sumZ/(numOfNeignbors);
    }
    
    *vx =  (sumX - theBoid->transx)*0.01;
    *vy =  (sumY - theBoid->transy)*0.01;
    *vz =  (sumZ - theBoid->transz)*0.01;
}

void ruleOfBirdsSeperation(Boid* boids, GLfloat *vx, GLfloat *vy, GLfloat *vz, Boid* theBoid, GLint numOfBoids, GLfloat distance){
    GLfloat sumX = 0, sumY =0, sumZ = 0;
    for (int i =0; i < numOfBoids; i++) {
        if (boids+i != theBoid) {
            if(sqrt( pow((boids+i)->transx - theBoid->transx,2) +pow((boids+i)->transy - theBoid->transy,2) +pow((boids+i)->transz - theBoid->transz,2)) < distance){
                sumX +=  -(boids+i)->transx + theBoid->transx;
                sumY +=  -(boids+i)->transy + theBoid->transy;
                sumZ +=  -(boids+i)->transz + theBoid->transz;
            }
        }
    }
    *vx =  sumX ;
    *vy =  sumY ;
    *vz =  sumZ ;
    
}

void ruleOfBirdsVelocityMatch(GLfloat radius, Boid* boids, GLfloat *vx, GLfloat *vy, GLfloat *vz, Boid* theBoid, GLint numOfBoids){
    GLfloat sumX = 0, sumY =0, sumZ = 0;
    GLint numOfNeignbors = 0;
    for (int i =0; i < numOfBoids; i++) {
        if (boids+i != theBoid) {
            if(sqrt( pow((boids+i)->transx - theBoid->transx,2) +pow((boids+i)->transy - theBoid->transy,2) +pow((boids+i)->transz - theBoid->transz,2)) < radius){
                sumX+= (boids+i)->currentVx;
                sumY+= (boids+i)->currentVy;
                sumZ+= (boids+i)->currentVz;
                numOfNeignbors ++;
            }
        }
    }
    
    if (numOfNeignbors > 1) {
        sumX = sumX/(numOfNeignbors);
        sumY = sumY/(numOfNeignbors);
        sumZ = sumZ/(numOfNeignbors);
    }
    
    *vx =  (sumX - theBoid->currentVx)*0.15;
    *vy =  (sumY - theBoid->currentVy)*0.15;
    *vz =  (sumZ - theBoid->currentVz)*0.15;
}


void anotherLookAt(GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ, GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat upX, GLfloat upY, GLfloat upZ,
                   GLfloat *m1, GLfloat *m2,GLfloat *m3,GLfloat *m4,
                   GLfloat *m5,GLfloat *m6, GLfloat *m7, GLfloat *m8,
                   GLfloat *m9,GLfloat *m10,GLfloat *m11,GLfloat *m12,
                   GLfloat *m13, GLfloat *m14,GLfloat *m15,GLfloat *m16){
    GLfloat f[3] = {centerX - eyeX, centerY - eyeY, centerZ - eyeZ};
    GLfloat up[3] = {upX, upY, upZ};
    GLfloat s[3] = {0,0,0};
    GLfloat u[3] = {0,0,0};
    
    normalizeVec(&f[0], &f[1], &f[2]);
    normalizeVec(&up[0], &up[1], &up[2]);
    
    crossProd(f[0], f[1], f[2], up[0], up[1], up[2], &s[0], &s[1], &s[2]);
    
    normalizeVec(&s[0], &s[1], &s[2]);
    crossProd(s[0], s[1], s[2], f[0], f[1], f[2], &u[0], &u[1], &u[2]);
    
    *m1 =s[0];
    *m2 =u[0];
    *m3 =-f[0];
    *m4 = 0;
    
    *m5 = s[1];
    *m6 = u[1];
    *m7 = -f[1];
    *m8 = 0;
    
    *m9 = s[2];
    *m10 = u[2];
    *m11 = -f[2];
    *m12 = 0;
    
    *m13 = 0;
    *m14 = 0;
    *m15 = 0;
    *m16 = 1;
}

void anotherPerspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar, GLfloat *m1, GLfloat *m2,GLfloat *m3,GLfloat *m4,GLfloat *m5,GLfloat *m6, GLfloat *m7, GLfloat *m8,GLfloat *m9,GLfloat *m10,GLfloat *m11,GLfloat *m12,GLfloat *m13, GLfloat *m14,GLfloat *m15,GLfloat *m16){
    GLfloat f = 1/(tan(fovy*0.5*3.1415926/180));
    
    *m1 = f/aspect ;
    *m2 = 0;
    *m3 = 0;
    *m4 = 0;
    
    *m5 = 0;
    *m6 = f;
    *m7 = 0;
    *m8 = 0;
    
    *m9 = 0;
    *m10 = 0;
    *m11 = (zFar + zNear)/(zNear -zFar);
    *m12 = -1;
    
    *m13 = 0;
    *m14 = 0;
    *m15 = (2*zFar*zNear)/(zNear -zFar);
    *m16 = 0;
    
    
}


