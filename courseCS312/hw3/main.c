
/*************************************************************************
 homework 3
 Xuan Huang
 boids behavior imitation
 *************************************************************************/

#include "func.h"
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define GOALINDEX 10000  // GOALINDEX = array size for boids = real capacity of boids +1
#define VIEWSIZE 2
#define UPVWEIGH 0.005
#define EXTRGOALTRANSVWEIGHXY 0.005
#define TURNINGSPPED 0.1
#define EXTRBOIDTRANSVWEIGHXY 0.002
#define BOIDWAITDIST 0.1
#define DEBUGSTEPFRAMECOUNT 60

#define BOIDSIZESCLARAR 0.5

#define EFFECRTRADIUS 0.1
#define TOGOALWEIGH 2
#define RULEONEGATHERWEIGH 2
#define RULETWOSEPERATIONWEIGH 10
#define RULETWOSEPERATIONDIST 0.05
#define RULETHREEVELOCITYMATCHWEIGH 1.5

enum{FALSE, TRUE};
enum{DEFAULTVIEW, TRAILINGVIEW, SIDEVIEW};
enum{KEYD, KEYP, KEYADD, KEYSUB, KEYV, KEYS, KEYINPUTTOTAL};

GLfloat boidObjectExample[21] = {BOIDSIZESCLARAR*0.05,0,0, 0,-0.05*BOIDSIZESCLARAR,0.05*BOIDSIZESCLARAR, 0.1*BOIDSIZESCLARAR,0,0, 0,0.05*BOIDSIZESCLARAR,0.05*BOIDSIZESCLARAR, 0,0,0.5, 1,0,0, 1,0,0};
GLint DEBUG = FALSE, ifPress = FALSE, leftPress = FALSE, rightPress = FALSE, upPress = FALSE, downPress = FALSE, repeatPress = FALSE;
GLint keyInput[KEYINPUTTOTAL] = {FALSE,FALSE,FALSE,FALSE,FALSE, FALSE};
GLfloat constForVelocity = 1;
GLint timeCount = 0, realTimeCount = 0;

Boid boids[GOALINDEX+1];
GLint currentNumOfBirds = 0;
GLint viewMode = DEFAULTVIEW;


void draw(){
    // clear to background color
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    
    GLfloat centroidOfBoidsMass[3] = {0,0,0} ;
    GLfloat midPointOfView[3] = {0,0,0};
    GLfloat distCtoG = 0, maxDistBtoC = 0;
    GLfloat vectCtoG[3] = {0,0,0};
    
    
    if (currentNumOfBirds > 0) {
        GLfloat tmpDist = 0;
        
        for (int i =0; i < currentNumOfBirds; i++) {
            centroidOfBoidsMass[0] += boids[i].transx;
            centroidOfBoidsMass[1] += boids[i].transy;
            centroidOfBoidsMass[2] += boids[i].transz;
            
            tmpDist = sqrt(pow(boids[i].transx - boids[GOALINDEX].transx,2)
                           +pow(boids[i].transy - boids[GOALINDEX].transy,2)
                           +pow(boids[i].transz - boids[GOALINDEX].transz,2));
            
            if (tmpDist > distCtoG) {
                maxDistBtoC = tmpDist;
            }
        }
        
        distCtoG = sqrt(pow(boids[GOALINDEX].transx - centroidOfBoidsMass[0],2)
                        +pow(boids[GOALINDEX].transy - centroidOfBoidsMass[1],2)
                        +pow(boids[GOALINDEX].transz - centroidOfBoidsMass[2],2));
        
        centroidOfBoidsMass[0] = centroidOfBoidsMass[0]/currentNumOfBirds;
        centroidOfBoidsMass[1] = centroidOfBoidsMass[1]/currentNumOfBirds;
        centroidOfBoidsMass[2] = centroidOfBoidsMass[2]/currentNumOfBirds;
        
        vectCtoG[0] = boids[GOALINDEX].transx - centroidOfBoidsMass[0];
        vectCtoG[1] = boids[GOALINDEX].transy - centroidOfBoidsMass[1];
        vectCtoG[2] = boids[GOALINDEX].transz - centroidOfBoidsMass[2];
        
        normalizeVec(&vectCtoG[0], &vectCtoG[1], &vectCtoG[2]);
        
        midPointOfView[0] = (boids[GOALINDEX].transx + centroidOfBoidsMass[0])*0.5;
        midPointOfView[1] = (boids[GOALINDEX].transy + centroidOfBoidsMass[1])*0.5;
        midPointOfView[2] = (boids[GOALINDEX].transz + centroidOfBoidsMass[2])*0.5;
        
        GLfloat mat[16] = {0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0};
        GLfloat matp[16] = {0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0};
        
        switch(viewMode) {
            case DEFAULTVIEW :
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                anotherPerspective(60, 1, 0.1, 10,&matp[0], &matp[1],&matp[2],&matp[3],
                                   &matp[4], &matp[5],&matp[6],&matp[7],
                                   &matp[8], &matp[9],&matp[10],&matp[11],
                                   &matp[12], &matp[13],&matp[14],&matp[15]);
                glMultMatrixf(matp);
                glMatrixMode(GL_MODELVIEW);
                anotherLookAt(0, 0, .5*VIEWSIZE, midPointOfView[0], midPointOfView[1], midPointOfView[2], 0, 0 ,1,
                              &mat[0], &mat[1],&mat[2],&mat[3],
                              &mat[4], &mat[5],&mat[6],&mat[7],
                              &mat[8], &mat[9],&mat[10],&mat[11],
                              &mat[12], &mat[13],&mat[14],&mat[15]);
                glMultMatrixf(mat);
                glTranslatef(0,0, -0.5*VIEWSIZE);
                break;
            case TRAILINGVIEW :
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                anotherPerspective(30, 1, 0.1, 20,
                                   &matp[0], &matp[1],&matp[2],&matp[3],
                                   &matp[4], &matp[5],&matp[6],&matp[7],
                                   &matp[8], &matp[9],&matp[10],&matp[11],
                                   &matp[12], &matp[13],&matp[14],&matp[15]);
                glMultMatrixf(matp);
                
                glMatrixMode(GL_MODELVIEW);
                gluLookAt(centroidOfBoidsMass[0] - 0.3*(distCtoG+2*maxDistBtoC)*vectCtoG[0],
                          centroidOfBoidsMass[1] - 0.3*(distCtoG+2*maxDistBtoC)*vectCtoG[1],
                          centroidOfBoidsMass[2]- 0.5*(distCtoG+2*maxDistBtoC)*vectCtoG[2] + 0.2*(distCtoG+maxDistBtoC),
                          midPointOfView[0], midPointOfView[1], midPointOfView[2],
                          0, 0 ,1);
                break;
            case SIDEVIEW :{
                GLfloat p[3] = {0,0,0};
                crossProd(0,0,1,  vectCtoG[0],vectCtoG[1],vectCtoG[2],  &p[0], &p[1], &p[2]);
                
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                anotherPerspective(40, 1, 0.1, 20,
                                   &matp[0], &matp[1],&matp[2],&matp[3],
                                   &matp[4], &matp[5],&matp[6],&matp[7],
                                   &matp[8], &matp[9],&matp[10],&matp[11],
                                   &matp[12], &matp[13],&matp[14],&matp[15]);
                glMultMatrixf(matp);
                
                glMatrixMode(GL_MODELVIEW);
                gluLookAt(midPointOfView[0] - 0.3*(distCtoG+2*maxDistBtoC)*p[0],
                          midPointOfView[1] - 0.3*(distCtoG+2*maxDistBtoC)*p[1],
                          midPointOfView[2]- 0.5*(distCtoG+5*maxDistBtoC)*p[2] + 0.2*(distCtoG + maxDistBtoC),
                          midPointOfView[0], midPointOfView[1], midPointOfView[2],
                          0, 0 ,1);
                break;
            }
            default:
                break;
        }
    }else{  // no bird on site
        GLfloat mat[16] = {0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0};
        GLfloat matp[16] = {0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0};
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        anotherPerspective(60, 1, 0.1, 20,&matp[0], &matp[1],&matp[2],&matp[3],
                           &matp[4], &matp[5],&matp[6],&matp[7],
                           &matp[8], &matp[9],&matp[10],&matp[11],
                           &matp[12], &matp[13],&matp[14],&matp[15]);
        glMultMatrixf(matp);
        glMatrixMode(GL_MODELVIEW);
        anotherLookAt(0, 0, VIEWSIZE, 0, 0, 0, 0, 1 ,0,
                      &mat[0], &mat[1],&mat[2],&mat[3],
                      &mat[4], &mat[5],&mat[6],&mat[7],
                      &mat[8], &mat[9],&mat[10],&mat[11],
                      &mat[12], &mat[13],&mat[14],&mat[15]);
        glMultMatrixf(mat);
        glTranslatef(0,0, -VIEWSIZE);
    }
    
    
    drawCheckBoard();
    
    glPushMatrix();
    glTranslatef(boids[GOALINDEX].transx,boids[GOALINDEX].transy,boids[GOALINDEX].transz);
    
    if(boids[GOALINDEX].currentVx != 0 || boids[GOALINDEX].currentVy!= 0 || boids[GOALINDEX].currentVz!= 0) {
        glTranslatef(boids[GOALINDEX].x1, boids[GOALINDEX].y1, boids[GOALINDEX].z1);
        glRotatef( twoDAngle(1,0 ,boids[GOALINDEX].currentVx,boids[GOALINDEX].currentVy)*180/3.1415926, 0, 0, 1);
        glTranslatef(-boids[GOALINDEX].x1, -boids[GOALINDEX].y1, -boids[GOALINDEX].z1);
    }
    
    drawCube(boids[GOALINDEX]);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(boids[GOALINDEX].transx,boids[GOALINDEX].transy,0.01);
    
    if(boids[GOALINDEX].currentVx != 0 || boids[GOALINDEX].currentVy!= 0 || boids[GOALINDEX].currentVz!= 0) {
        glTranslatef(boids[GOALINDEX].x1, boids[GOALINDEX].y1, boids[GOALINDEX].z1);
        glRotatef( twoDAngle(1,0 ,boids[GOALINDEX].currentVx,boids[GOALINDEX].currentVy)*180/3.1415926, 0, 0, 1);
        glTranslatef(-boids[GOALINDEX].x1, -boids[GOALINDEX].y1, -boids[GOALINDEX].z1);
    }
    drawShadow(boids[GOALINDEX]);
    glPopMatrix();
    
    if (DEBUG == TRUE) {
        printf("boids[GOALINDEX].transx transy transz: %f, %f, %f \n", boids[GOALINDEX].transx,boids[GOALINDEX].transy, boids[GOALINDEX].transz);
        printf("goal rotate angle %f \n", twoDAngle(1,0 ,boids[GOALINDEX].currentVx,boids[GOALINDEX].currentVy)*180/3.1415926);
    }
    
    
    for (int i =0; i < currentNumOfBirds; i++) {
        
        glPushMatrix();
        glTranslatef(boids[i].transx,boids[i].transy,boids[i].transz);
        if(boids[i].currentVx != 0 || boids[i].currentVy!= 0 || boids[i].currentVz!= 0) {
            GLfloat turningAngle = twoDAngle(1,0, boids[i].currentVx,boids[i].currentVy)*180/3.1415926;
            
            glTranslatef(boids[i].x1, boids[i].y1, boids[i].z1);
            glRotatef(turningAngle, 0,0,1);
            
            glTranslatef(-boids[i].x1, -boids[i].y1, -boids[i].z1);
        }
        
        drawBoid(boids[i]);
        glPopMatrix();
        
        glPushMatrix();
        glTranslatef(boids[i].transx,boids[i].transy,0.01);
        if(boids[i].currentVx != 0 || boids[i].currentVy!= 0 || boids[i].currentVz!= 0) {
            GLfloat turningAngle = twoDAngle(1,0, boids[i].currentVx,boids[i].currentVy)*180/3.1415926;
            glTranslatef(boids[i].x1, boids[i].y1, boids[i].z1);
            glRotatef(turningAngle, 0,0,1);
            glTranslatef(-boids[i].x1, -boids[i].y1, -boids[i].z1);
        }
        drawShadow(boids[i]);
        
        glPopMatrix();
        
        if (DEBUG == TRUE) {
            printf("boids[%d].transx transy transz: %f, %f, %f \n", i,boids[i].transx,boids[i].transy, boids[i].transz);
            printf("boids[%d] rotate angle %f \n", i,twoDAngle(1,0 ,boids[i].currentVx,boids[i].currentVy)*180/3.1415926);
        }
        
    }
    
    
    realTimeCount ++;
    if (realTimeCount == 3600) {
        realTimeCount = 0;
    }
    
    
    //update
    
    if (keyInput[KEYADD] == TRUE) {
        if(ifPress == TRUE){
            if(currentNumOfBirds <GOALINDEX){
                Boid tmpBird = {boidObjectExample[0],boidObjectExample[1],boidObjectExample[2], boidObjectExample[3], boidObjectExample[4],boidObjectExample[5],boidObjectExample[6], boidObjectExample[7],boidObjectExample[8],boidObjectExample[9], boidObjectExample[10],boidObjectExample[11],0.02*(35-realTimeCount%70),0.01*(20-realTimeCount%40),0.01*(realTimeCount%30), boidObjectExample[15], boidObjectExample[16],boidObjectExample[17],boidObjectExample[18], boidObjectExample[19],boidObjectExample[20]};
                boids[currentNumOfBirds] = tmpBird;
                currentNumOfBirds ++;
            }
            ifPress = FALSE;
        }
        keyInput[KEYADD] = FALSE;
    }
    if (keyInput[KEYSUB] == TRUE) {
        if(ifPress == TRUE){
            if(currentNumOfBirds >0)
                currentNumOfBirds --;
            ifPress = FALSE;
        }
        keyInput[KEYSUB] = FALSE;
    }
    if (keyInput[KEYV] == TRUE) {
        constForVelocity += 0.1;
        keyInput[KEYV] = FALSE;
    }
    if (keyInput[KEYS] == TRUE) {
        constForVelocity -= 0.1;
        keyInput[KEYS] = FALSE;
    }
    if (keyInput[KEYP] == TRUE) {
        if(ifPress == TRUE && repeatPress == FALSE){
            DEBUG = DEBUG+TRUE;
            if (DEBUG > TRUE) {
                DEBUG = FALSE;
            }
        }
        keyInput[KEYP] = FALSE;
    }
    if (keyInput[KEYD] == TRUE) {
        if(ifPress == TRUE){
            DEBUG = DEBUG+TRUE;
            if (DEBUG > TRUE) {
                DEBUG = FALSE;
            }
            ifPress = FALSE;
        }
        keyInput[KEYD] = FALSE;
    }
    
    
    if (DEBUG == FALSE) {
        timeCount ++;
        if (timeCount == 3600) {
            timeCount = 0;
        }
        
        //
        //
        // update goal movement
        //
        //
        //
        
        boids[GOALINDEX].lastX1 = boids[GOALINDEX].currentVx;
        boids[GOALINDEX].lastY1 = boids[GOALINDEX].currentVy;
        
        if (leftPress == TRUE) {
            GLfloat v1, v2, v3;
            crossProd(boids[GOALINDEX].lastX1,boids[GOALINDEX].lastY1,0,  0,0,-1,  &v1, &v2, &v3);
            
            
            GLfloat directionX = v1;
            GLfloat directionY = v2;
            GLfloat directionZ = 0;
            
            normalizeVec(&directionX, &directionY, &directionZ);
            
            boids[GOALINDEX].currentVx += TURNINGSPPED * directionX;
            boids[GOALINDEX].currentVy += TURNINGSPPED * directionY;
            
            
            leftPress = FALSE;
        }
        
        
        if (rightPress == TRUE) {
            GLfloat v1, v2, v3;
            crossProd(boids[GOALINDEX].lastX1,boids[GOALINDEX].lastY1,0,  0,0,1,  &v1, &v2, &v3);
            normalizeVec(&v1, &v2, &v3);
            
            GLfloat directionX = v1;
            GLfloat directionY = v2;
            GLfloat directionZ = 0;
            normalizeVec(&directionX, &directionY, &directionZ);
            
            boids[GOALINDEX].currentVx += TURNINGSPPED * directionX;
            boids[GOALINDEX].currentVy += TURNINGSPPED * directionY;
            
            rightPress = FALSE;
        }
        
        
        
        if (upPress == TRUE) {
            if(boids[GOALINDEX].transz < VIEWSIZE/2)
                boids[GOALINDEX].transz += VIEWSIZE*UPVWEIGH;
            upPress = FALSE;
        }
        
        if (downPress == TRUE) {
            if(boids[GOALINDEX].transz >0)
                boids[GOALINDEX].transz -= VIEWSIZE*UPVWEIGH;
            downPress = FALSE;
        }
        
        normalizeVec(&boids[GOALINDEX].currentVx, &boids[GOALINDEX].currentVy, &boids[GOALINDEX].currentVz);
        
        if (constForVelocity >= 2) {
            constForVelocity = 2;
        }else if(constForVelocity <= 0){
            constForVelocity = 0;
        }
        
        boids[GOALINDEX].currentVx *= constForVelocity;
        boids[GOALINDEX].currentVy *= constForVelocity;
        boids[GOALINDEX].currentVz *= constForVelocity;
        
        boids[GOALINDEX].transx += EXTRGOALTRANSVWEIGHXY*boids[GOALINDEX].currentVx;
        boids[GOALINDEX].transy += EXTRGOALTRANSVWEIGHXY*boids[GOALINDEX].currentVy;
        
        
        //if go out of bound, turn around (bouncing)
        
        
        if(boids[GOALINDEX].transx >= VIEWSIZE/2 || boids[GOALINDEX].transx <= -VIEWSIZE/2){
            boids[GOALINDEX].currentVx *= -1;
        }
        
        if(boids[GOALINDEX].transy >= VIEWSIZE/2 || boids[GOALINDEX].transy <= -VIEWSIZE/2){
            boids[GOALINDEX].currentVy *= -1;
        }
        
        if(boids[GOALINDEX].transz >= VIEWSIZE/2 || boids[GOALINDEX].transz <= -VIEWSIZE/2){
            boids[GOALINDEX].currentVz *= -1;
        }
        
        //
        //
        // update boids movement
        //
        //
        
        if(currentNumOfBirds > 0){
            for (int i =0; i < currentNumOfBirds; i++) {
                if (sqrt( pow(boids[GOALINDEX].transx - boids[i].transx,2) +pow(boids[GOALINDEX].transy - boids[i].transy,2) +pow(boids[GOALINDEX].transz - boids[i].transz,2)) > BOIDWAITDIST) {
                    
                    // update position
                    
                    boids[i].transx += VIEWSIZE*EXTRBOIDTRANSVWEIGHXY*boids[i].currentVx;
                    boids[i].transy += VIEWSIZE*EXTRBOIDTRANSVWEIGHXY*boids[i].currentVy;
                }
                //set moving vector
                
                boids[i].lastX1 = boids[i].currentVx;
                boids[i].lastY1 = boids[i].currentVy;
                
                GLfloat vx1 =0,vy1=0,vz1=0, vx2=0,vy2=0,vz2=0, vx3=0,vy3=0,vz3=0;
                
                ruleOfBirdsGatherToCentroid(EFFECRTRADIUS, boids, &vx1, &vy1, &vz1, &boids[i], currentNumOfBirds);
                ruleOfBirdsSeperation(boids, &vx2, &vy2, &vz2, &boids[i], currentNumOfBirds, RULETWOSEPERATIONDIST);
                ruleOfBirdsVelocityMatch(EFFECRTRADIUS, boids, &vx3, &vy3, &vz3, &boids[i], currentNumOfBirds);
                
                GLfloat directionX = TOGOALWEIGH*(boids[GOALINDEX].transx - boids[i].transx)
                + RULEONEGATHERWEIGH*vx1 + RULETWOSEPERATIONWEIGH *vx2 + RULETHREEVELOCITYMATCHWEIGH*vx3;
                GLfloat directionY = TOGOALWEIGH*(boids[GOALINDEX].transy - boids[i].transy)
                + RULEONEGATHERWEIGH*vy1 + RULETWOSEPERATIONWEIGH *vy2 + RULETHREEVELOCITYMATCHWEIGH*vx3;
                GLfloat directionZ = 0;
                normalizeVec(&directionX, &directionY, &directionZ);
                
                boids[i].currentVx += TURNINGSPPED*directionX;
                boids[i].currentVy += TURNINGSPPED*directionY;
                boids[i].currentVz = 0;
                
                boids[i].transz += UPVWEIGH*TOGOALWEIGH*(boids[GOALINDEX].z1 + boids[GOALINDEX].transz - boids[i].z1 - boids[i].transz) + UPVWEIGH*RULEONEGATHERWEIGH*vz1;

                
                normalizeVec(&boids[i].currentVx, &boids[i].currentVy, &boids[i].currentVz);
                
            }
            
            
        }
        
        
        
    }
    repeatPress = FALSE;
    
}


void init() {
    // Set the clear color to black
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    
    
    Boid tmpBird = {boidObjectExample[0],boidObjectExample[1],boidObjectExample[2], boidObjectExample[3], boidObjectExample[4],boidObjectExample[5],boidObjectExample[6], boidObjectExample[7],boidObjectExample[8],boidObjectExample[9], boidObjectExample[10],boidObjectExample[11],boidObjectExample[12], boidObjectExample[13],boidObjectExample[14], boidObjectExample[15], boidObjectExample[16],boidObjectExample[17],boidObjectExample[18], boidObjectExample[19],boidObjectExample[20]};
    boids[GOALINDEX] = tmpBird;
    
    for(int i = 0; i<5; i++){
        if(currentNumOfBirds <GOALINDEX){
            Boid tmpBird = {boidObjectExample[0],boidObjectExample[1],boidObjectExample[2], boidObjectExample[3], boidObjectExample[4],boidObjectExample[5],boidObjectExample[6], boidObjectExample[7],boidObjectExample[8],boidObjectExample[9], boidObjectExample[10],boidObjectExample[11],0.02*i,0.1*i,0.3*i, boidObjectExample[15], boidObjectExample[16],boidObjectExample[17],boidObjectExample[18], boidObjectExample[19],boidObjectExample[20]};
            boids[currentNumOfBirds] = tmpBird;
            currentNumOfBirds ++;
        }
    }
    
    
    boids[GOALINDEX].currentVx = 0.8;
    boids[GOALINDEX].currentVy = 0.3;
    boids[GOALINDEX].currentVz = 0;
    
    
    //glEnable(GL_CULL);
}

void reshape(GLFWwindow *w, int width, int height){
    printf("Got a Reshape Event");
    printf(":\t width = %d height = %d\n", width, height);
    
    // Set the new viewport size
    glViewport(0, 0, width, height);
}

void keyboard(GLFWwindow *w, int key, int scancode, int action, int mods) {
    //printf("Got a Keyboard Event: ");
    //printf(" %d, ", key);
    
    switch(action) {
        case GLFW_PRESS :
            ifPress = TRUE;
            //printf("pressed,\t");
            break;
        case GLFW_RELEASE :
            //printf("released,\t");
            break;
        case GLFW_REPEAT :
            repeatPress = TRUE;
            //printf("repeated,\t");
            break;
        default :
            //printf("shouldn't happen\t");
            break;
    }
    
    switch(mods) {
        case GLFW_MOD_SHIFT :
            //printf("shift held\n");
            break;
        case GLFW_MOD_ALT :
            //printf("alt held\n");
            break;
        case GLFW_MOD_CONTROL :
            //printf("ctrl held\n");
            break;
        default :
            //printf("no modifiers.\n");
            break;
    }
    
    switch(key) {
        case GLFW_KEY_ESCAPE :
        case 'q' :
        case 'Q':
            glfwSetWindowShouldClose(w, GL_TRUE);
            break;
        case 'v' :
        case 'V':
            keyInput[KEYV] = TRUE;
            break;
        case 's' :
        case 'S':
            keyInput[KEYS] = TRUE;
            break;
        case 'd' :
        case 'D':
            keyInput[KEYP] = TRUE;
            break;
        case 'p' :
        case 'P':
            keyInput[KEYD] = TRUE;
            break;
            
        case 'w':
        case 'W':
            viewMode = DEFAULTVIEW ;
            break;
            
        case 't':
        case 'T':
            viewMode = TRAILINGVIEW;
            break;
        case 'r':
        case 'R':
            viewMode = SIDEVIEW;
            break;
            
        case GLFW_KEY_LEFT :
            leftPress = TRUE;
            break;
        case GLFW_KEY_RIGHT :
            rightPress = TRUE;
            break;
        case GLFW_KEY_UP :
            upPress = TRUE;
            break;
        case GLFW_KEY_DOWN :
            downPress = TRUE;
            break;
            
        case GLFW_KEY_KP_ADD:{
            keyInput[KEYADD] = TRUE;
            break;
        }
        case GLFW_KEY_KP_SUBTRACT:{
            keyInput[KEYSUB] = TRUE;
            break;
        }
            
            
            
        default:
            break;
    }
}



int main(int argc, char **argv) {
    GLFWwindow* window;
    
    // Initialize the library
    if (!glfwInit())
        exit(EXIT_FAILURE);
    
    // Create a window and its OpenGL context
    window = glfwCreateWindow(400, 400, "Hello GL!", NULL, NULL);
    if (!window){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    glfwSetWindowPos(window, 800, 400);
    // Make the window's context current
    glfwMakeContextCurrent(window);
    
    
    // Assign reshape() to be the function called whenever
    // a reshape event occurs
    glfwSetFramebufferSizeCallback(window, reshape);
    
    // Assign keyboard() to be the function called whenever
    // a key is pressed or released
    glfwSetKeyCallback(window, keyboard);
    
    
    
    init();
    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        
        draw();
        
        // Swap front and back buffers
        glfwSwapBuffers(window);
        
        // Poll for and process events
        glfwPollEvents();
    }
    
    glfwTerminate();
    exit(EXIT_SUCCESS);
}