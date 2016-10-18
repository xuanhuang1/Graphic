
#ifndef VARIBLES_H
#define VARIBLES_H

#ifdef __APPLE__  // include Mac OS X verions of headers
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#else // non-Mac OS X operating systems
#  include <GL/glew.h>
//uncomment these two and comment glfw3.h if you use glut on linux
//#  include <GL/freeglut.h>
//#  include <GL/freeglut_ext.h>
#  include <GLFW/glfw3.h>
#endif  // __APPLE__


#include "functions.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GOALINDEX 10000  // GOALINDEX = array size for boids = real capacity of boids +1
#define VIEWSIZE 2
#define UPVWEIGH 0.005
#define EXTRGOALTRANSVWEIGHXY 0.005
#define TURNINGSPPED 0.1
#define EXTRBOIDTRANSVWEIGHXY 0.002
#define BOIDWAITDIST 0.1
#define DEBUGSTEPFRAMECOUNT 60

#define BOIDSIZESCLARAR 1

#define EFFECRTRADIUS 0.1
#define TOGOALWEIGH 2
#define RULEONEGATHERWEIGH 2
#define RULETWOSEPERATIONWEIGH 10
#define RULETWOSEPERATIONDIST 0.1
#define RULETHREEVELOCITYMATCHWEIGH 1.5

#define GOALINDEXNUMTOTAL 1
#define BOIDSINDEXNUMTOTAL 1
#define SHADOWINDEXTOTAL 1
#define NUMOFGRIDSINCHECKERBOARD 181

#define VERTEXATTRIBSIZE 6
#define POINTSPERBIRD 4



enum{FALSE, TRUE};
enum{DEFAULTVIEW, TRAILINGVIEW, SIDEVIEW};
enum{KEYD, KEYP, KEYADD, KEYSUB, KEYV, KEYS, KEYINPUTTOTAL};

GLfloat boidObjectExample[21] = {0,0,0, -BOIDSIZESCLARAR*0.05,-0.05*BOIDSIZESCLARAR,0.05*BOIDSIZESCLARAR, 0.05*BOIDSIZESCLARAR,0,0,
    -BOIDSIZESCLARAR*0.05,0.05*BOIDSIZESCLARAR,0.05*BOIDSIZESCLARAR, 0,0,0.5, 1,0,0, 1,0,0};
GLint DEBUG = FALSE, ifPress = FALSE, leftPress = FALSE, rightPress = FALSE, upPress = FALSE, downPress = FALSE, repeatPress = FALSE;
GLint keyInput[KEYINPUTTOTAL] = {FALSE,FALSE,FALSE,FALSE,FALSE, FALSE};
GLfloat constForVelocity = 1;
GLint timeCount = 0, realTimeCount = 0;
#define DARKGRAY  0.2 // SHADOW
#define LIGHTGRAY 0.5 // CHECKERBOARD

GLuint program;

GLuint vao, vbo1, vbo2, pos, col, ind;

vec3 trans = vec3(0,0,0);
vec4 rotat = vec4(0,0,1, 0);

GLint MV;


Boid boids[GOALINDEX+1];
GLint currentNumOfBirds = 0;
GLint viewMode = DEFAULTVIEW;


//goal + boidExample +shadow + checkerboard
GLfloat allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL+NUMOFGRIDSINCHECKERBOARD)*POINTSPERBIRD][VERTEXATTRIBSIZE];
GLuint allElements[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL+NUMOFGRIDSINCHECKERBOARD)][VERTEXATTRIBSIZE];


void drawBoid(Boid b, mat4 inputMat);
void drawCheckBoard(mat4 inputMat);
void drawGoal(Boid b, mat4 inputMat);
void drawShadow(Boid b, mat4 inputMat);
void updateKeyboard();
void update();
void initAll();
mat4 switchPersp(mat4 ProjectionMatrix, mat4 ModelViewMatrix);


#endif
