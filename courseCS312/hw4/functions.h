

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structs.h"


#define GRIDCOLNUM 10
#define GRIDLENGTH .1

#define VIEWSIZE 2


vec3 crossProd(vec3 v1, vec3 v2){
    return vec3(v1.vec3arr[1]*v2.vec3arr[2]-v1.vec3arr[2]*v2.vec3arr[1],
                v1.vec3arr[2]*v2.vec3arr[0]-v1.vec3arr[0]*v2.vec3arr[2],
                v1.vec3arr[0]*v2.vec3arr[1]-v1.vec3arr[1]*v2.vec3arr[0]);
}

GLfloat dotProd(vec3 v1, vec3 v2){
    return v1.vec3arr[0]*v2.vec3arr[0]+v1.vec3arr[1]*v2.vec3arr[1]+
    v1.vec3arr[2]*v2.vec3arr[2];
}

mat4 anotherTranslatef(vec3 trans){
    return mat4(1,   0,  0,  0,
                0,   1,  0,  0,
                0,   0,  1,  0,
                trans.vec3arr[0],   trans.vec3arr[1],  trans.vec3arr[2],  1);
}

mat4 anotherRotatef(GLfloat angle, vec3 trans){
    GLfloat c = cos(angle*3.14/180);
    GLfloat s = sin(angle*3.14/180);
    trans.normalize();
    
    return mat4(trans.vec3arr[0]*trans.vec3arr[0]*(1-c)+c, trans.vec3arr[0]*trans.vec3arr[1]*(1-c) + trans.vec3arr[2]*s,  trans.vec3arr[0]*trans.vec3arr[2]*(1-c) - trans.vec3arr[1]*s,  0,
                trans.vec3arr[0]*trans.vec3arr[1]*(1-c) - trans.vec3arr[2]*s, trans.vec3arr[1]*trans.vec3arr[1]*(1-c)+c,  trans.vec3arr[1]*trans.vec3arr[2]*(1-c) + trans.vec3arr[0]*s, 0,
                trans.vec3arr[0]*trans.vec3arr[2]*(1-c) + trans.vec3arr[1]*s, trans.vec3arr[1]*trans.vec3arr[2]*(1-c) - trans.vec3arr[0]*s,  trans.vec3arr[2]*trans.vec3arr[2]*(1-c)+c,  0,
                0,   0,  0,  1);
}

mat4 anotherScalef(vec3 trans){
    return mat4(trans.vec3arr[0],   0,  0,  0,
                0,   trans.vec3arr[1],  0,  0,
                0,   0,  trans.vec3arr[2],  0,
                0,   0,                 0,  1);
}

mat4 anotherLookAt(vec3 eye, vec3 center, vec3 up){
    
    vec3 f = vec3(center.vec3arr[0] - eye.vec3arr[0],
              center.vec3arr[1] - eye.vec3arr[1],
              center.vec3arr[2] - eye.vec3arr[2]);

    vec3 s = vec3(0,0,0);
    vec3 u = vec3(0,0,0);
    vec3 ns = vec3(0,0,0);
    
    f.normalize();
    up.normalize();
    
    s = crossProd(f, up);
    
    s.normalize();
    u = crossProd(s, f);
    
    mat4 returnM = mat4(s.vec3arr[0], u.vec3arr[0], -f.vec3arr[0], 0,
                        s.vec3arr[1], u.vec3arr[1], -f.vec3arr[1], 0,
                        s.vec3arr[2], u.vec3arr[2], -f.vec3arr[2], 0,
                        0,0,0,1);
    
    return anotherTranslatef(vec3(-eye.vec3arr[0], -eye.vec3arr[1],-eye.vec3arr[2])).mul(returnM);
    //return returnM;
}

mat4 anotherPerspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar){
    GLfloat f = 1/(tan(fovy*0.5*3.141592653589793238462643383279502884197169399375105820974944/180));
    
    return mat4(f/aspect,   0,  0,                             0,
                0,          f,  0,                             0,
                0,          0,  (zFar + zNear)/(zNear -zFar),  -1,
                0,          0,  (2*zFar*zNear)/(zNear -zFar),  0);
    
    
}





//////////////////////////////////////////////



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
#endif
