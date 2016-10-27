// Two-Dimensional Sierpinski Gasket
// Generated using randomly selected vertices and bisection

#include "common.h"
#include "varibles.h"


static GLuint make_bo(GLenum type, const void *buf, GLsizei buf_size) {
    GLuint bufnum;
    glGenBuffers(1, &bufnum);
    glBindBuffer(type, bufnum);
    glBufferData(type, buf_size, buf, GL_STATIC_DRAW);
    return bufnum;
}


void draw(){
    
    //mat4 clipM = mat4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
    
    mat4 ModelViewMatrix= mat4(0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0);
    mat4 ProjectionMatrix = mat4(0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0);

    mat4 ModelViewProjectionMatrix = switchPersp(ModelViewMatrix, ProjectionMatrix);
    
    //drawCheckBoard(ModelViewProjectionMatrix);
    
    drawCheckBoard (ModelViewProjectionMatrix);
    drawGoal(boids[GOALINDEX], ModelViewProjectionMatrix);
    
    for (int i =0; i < currentNumOfBirds; i++) {
        drawBoid(boids[i], ModelViewProjectionMatrix);
        drawShadow(boids[i], ModelViewProjectionMatrix);
        if (DEBUG == TRUE) {
            printf("boids[%d].transx transy transz: %f, %f, %f \n", i,boids[i].transx,boids[i].transy, boids[i].transz);
            printf("boids[%d] rotate angle %f \n", i,twoDAngle(1,0 ,boids[i].currentVx,boids[i].currentVy)*180/3.1415926);
        }
    }
    //rotat.vec4arr[3] += 1;
    update();
    //printf("%f ",rotat.vec4arr[3]);
}
void initAll(){
    
    
    //
    //
    // boids and goal
    //
    //
    
    
    allVertices[0][0] = boids[GOALINDEX].x1;
    allVertices[0][1] = boids[GOALINDEX].y1;
    allVertices[0][2] = boids[GOALINDEX].z1;
    allVertices[0][3] = 1;
    allVertices[0][4] = 1;
    allVertices[0][5] = 1;
    allVertices[1][0] = boids[GOALINDEX].x2;
    allVertices[1][1] = boids[GOALINDEX].y2;
    allVertices[1][2] = boids[GOALINDEX].z2;
    allVertices[1][3] = 1;
    allVertices[1][4] = 1;
    allVertices[1][5] = 1;
    allVertices[2][0] = boids[GOALINDEX].x3;
    allVertices[2][1] = boids[GOALINDEX].y3;
    allVertices[2][2] = boids[GOALINDEX].z3;
    allVertices[2][3] = 1;
    allVertices[2][4] = 1;
    allVertices[2][5] = 1;
    allVertices[3][0] = boids[GOALINDEX].x4;
    allVertices[3][1] = boids[GOALINDEX].y4;
    allVertices[3][2] = boids[GOALINDEX].z4;
    allVertices[3][3] = 1;
    allVertices[3][4] = 1;
    allVertices[3][5] = 1;
    
    for (int i = 0; i<POINTSPERBIRD; i++) {
        for (int j = 0; j<VERTEXATTRIBSIZE; j++) {
            allVertices[i+POINTSPERBIRD*GOALINDEXNUMTOTAL][j] = allVertices[i][j];
        }
    }
    
    allVertices[5][4] = 0;
    allVertices[5][5] = 0;
    allVertices[6][5] = 0;
    allVertices[7][4] = 0;
    allVertices[7][3] = 0;
    
    
    //
    //
    //  shadow
    //
    //
    
    for (int i = 0; i<POINTSPERBIRD; i++) {
        for (int j = 0; j<VERTEXATTRIBSIZE; j++) {
            if (j<2) {
                allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL)*POINTSPERBIRD+i][j] = allVertices[i][j];
            }else if (j==2) {
                allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL)*POINTSPERBIRD+i][j] = 0.01;
            }else{
                allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL)*POINTSPERBIRD+i][j] = DARKGRAY;
            }
        }
    }
    
    
    //
    //
    //  init checkerboard
    //
    //
    
    for(int i = 0; i< GRIDCOLNUM*GRIDCOLNUM*POINTSPERBIRD; i+=POINTSPERBIRD){
        int k = i/POINTSPERBIRD;
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL + k)* POINTSPERBIRD ][0] = -(GRIDCOLNUM*GRIDLENGTH) + 2*GRIDLENGTH*(k%GRIDCOLNUM);
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL + k)* POINTSPERBIRD ][1] = -(GRIDCOLNUM*GRIDLENGTH) + 2*GRIDLENGTH*(k/GRIDCOLNUM);
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL  +k)* POINTSPERBIRD ][2] = 0;
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL  +k)* POINTSPERBIRD ][3] = LIGHTGRAY;
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL  +k)* POINTSPERBIRD ][4] = LIGHTGRAY;
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL  +k)* POINTSPERBIRD ][5] = LIGHTGRAY;
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL  +k)* POINTSPERBIRD +1][0] =-(GRIDCOLNUM*GRIDLENGTH) + GRIDLENGTH+ 2*GRIDLENGTH*(k%GRIDCOLNUM);
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL  +k)* POINTSPERBIRD +1][1] =-(GRIDCOLNUM*GRIDLENGTH)+ 2*GRIDLENGTH*(k/GRIDCOLNUM);
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL  +k)* POINTSPERBIRD +1][2] = 0;
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL  +k)* POINTSPERBIRD +1][3] = LIGHTGRAY;
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL  +k)* POINTSPERBIRD +1][4] = LIGHTGRAY;
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL  +k)* POINTSPERBIRD +1][5] = LIGHTGRAY;
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL  +k)* POINTSPERBIRD +2][0] = -(GRIDCOLNUM*GRIDLENGTH) + GRIDLENGTH+ 2*GRIDLENGTH*(k%GRIDCOLNUM);
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL  +k)* POINTSPERBIRD +2][1] = -(GRIDCOLNUM*GRIDLENGTH) + GRIDLENGTH+ 2*GRIDLENGTH*(k/GRIDCOLNUM);
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL  +k)* POINTSPERBIRD +2][2] = 0;
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL  +k)* POINTSPERBIRD +2][3] = LIGHTGRAY;
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL  +k)* POINTSPERBIRD +2][4] = LIGHTGRAY;
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL  +k)* POINTSPERBIRD +2][5] = LIGHTGRAY;
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL  +k)* POINTSPERBIRD +3][0] = -(GRIDCOLNUM*GRIDLENGTH)+ 2*GRIDLENGTH*(k%GRIDCOLNUM);
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL  +k)* POINTSPERBIRD +3][1] = -(GRIDCOLNUM*GRIDLENGTH) + GRIDLENGTH+ 2*GRIDLENGTH*(k/GRIDCOLNUM);
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL  +k)* POINTSPERBIRD +3][2] = 0;
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL  +k)* POINTSPERBIRD +3][3] = LIGHTGRAY;
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL  +k)* POINTSPERBIRD +3][4] = LIGHTGRAY;
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL  +k)* POINTSPERBIRD +3][5] = LIGHTGRAY;
        
        /*printf("%d : %f %f %f %f %f %f %f %f \n",(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL + k)* POINTSPERBIRD,
         -(GRIDCOLNUM*GRIDLENGTH) + 2*GRIDLENGTH*(k%GRIDCOLNUM),
         -(GRIDCOLNUM*GRIDLENGTH) + 2*GRIDLENGTH*(k/GRIDCOLNUM),
         -(GRIDCOLNUM*GRIDLENGTH) + GRIDLENGTH+ 2*GRIDLENGTH*(k%GRIDCOLNUM),
         -(GRIDCOLNUM*GRIDLENGTH)+ 2*GRIDLENGTH*(k/GRIDCOLNUM),
         -(GRIDCOLNUM*GRIDLENGTH) + GRIDLENGTH+ 2*GRIDLENGTH*(k%GRIDCOLNUM),
         -(GRIDCOLNUM*GRIDLENGTH) + GRIDLENGTH+ 2*GRIDLENGTH*(k/GRIDCOLNUM),
         -(GRIDCOLNUM*GRIDLENGTH)+ 2*GRIDLENGTH*(k%GRIDCOLNUM),
         -(GRIDCOLNUM*GRIDLENGTH) + GRIDLENGTH+ 2*GRIDLENGTH*(k/GRIDCOLNUM));*/
    }
    
    for(int i = 0; i< (GRIDCOLNUM-1)*(GRIDCOLNUM-1)*POINTSPERBIRD; i+=POINTSPERBIRD){
        int k = i/POINTSPERBIRD;
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL+GRIDCOLNUM*GRIDCOLNUM + k)* POINTSPERBIRD ][0] =GRIDLENGTH -(GRIDCOLNUM*GRIDLENGTH) + 2*GRIDLENGTH*(k%(GRIDCOLNUM-1));
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL+GRIDCOLNUM*GRIDCOLNUM + k)* POINTSPERBIRD ][1] =GRIDLENGTH -(GRIDCOLNUM*GRIDLENGTH) + 2*GRIDLENGTH*(k/(GRIDCOLNUM-1));
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL+GRIDCOLNUM*GRIDCOLNUM  +k)* POINTSPERBIRD ][2] = 0;
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL+GRIDCOLNUM*GRIDCOLNUM  +k)* POINTSPERBIRD ][3] = LIGHTGRAY;
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL+GRIDCOLNUM*GRIDCOLNUM  +k)* POINTSPERBIRD ][4] = LIGHTGRAY;
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL+GRIDCOLNUM*GRIDCOLNUM  +k)* POINTSPERBIRD ][5] = LIGHTGRAY;
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL+GRIDCOLNUM*GRIDCOLNUM  +k)* POINTSPERBIRD +1][0] =GRIDLENGTH-(GRIDCOLNUM*GRIDLENGTH) + GRIDLENGTH+ 2*GRIDLENGTH*(k%(GRIDCOLNUM-1));
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL+GRIDCOLNUM*GRIDCOLNUM  +k)* POINTSPERBIRD +1][1] =GRIDLENGTH-(GRIDCOLNUM*GRIDLENGTH)+ 2*GRIDLENGTH*(k/(GRIDCOLNUM-1));
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL+GRIDCOLNUM*GRIDCOLNUM  +k)* POINTSPERBIRD +1][2] = 0;
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL+GRIDCOLNUM*GRIDCOLNUM  +k)* POINTSPERBIRD +1][3] = LIGHTGRAY;
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL+GRIDCOLNUM*GRIDCOLNUM  +k)* POINTSPERBIRD +1][4] = LIGHTGRAY;
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL+GRIDCOLNUM*GRIDCOLNUM  +k)* POINTSPERBIRD +1][5] = LIGHTGRAY;
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL+GRIDCOLNUM*GRIDCOLNUM  +k)* POINTSPERBIRD +2][0] = GRIDLENGTH-(GRIDCOLNUM*GRIDLENGTH) + GRIDLENGTH+ 2*GRIDLENGTH*(k%(GRIDCOLNUM-1));
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL+GRIDCOLNUM*GRIDCOLNUM  +k)* POINTSPERBIRD +2][1] = GRIDLENGTH-(GRIDCOLNUM*GRIDLENGTH) + GRIDLENGTH+ 2*GRIDLENGTH*(k/(GRIDCOLNUM-1));
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL+GRIDCOLNUM*GRIDCOLNUM  +k)* POINTSPERBIRD +2][2] = 0;
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL+GRIDCOLNUM*GRIDCOLNUM  +k)* POINTSPERBIRD +2][3] = LIGHTGRAY;
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL+GRIDCOLNUM*GRIDCOLNUM  +k)* POINTSPERBIRD +2][4] = LIGHTGRAY;
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL+GRIDCOLNUM*GRIDCOLNUM  +k)* POINTSPERBIRD +2][5] = LIGHTGRAY;
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL+GRIDCOLNUM*GRIDCOLNUM  +k)* POINTSPERBIRD +3][0] = GRIDLENGTH-(GRIDCOLNUM*GRIDLENGTH)+ 2*GRIDLENGTH*(k%(GRIDCOLNUM-1));
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL+GRIDCOLNUM*GRIDCOLNUM  +k)* POINTSPERBIRD +3][1] = GRIDLENGTH-(GRIDCOLNUM*GRIDLENGTH) + GRIDLENGTH+ 2*GRIDLENGTH*(k/(GRIDCOLNUM-1));
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL+GRIDCOLNUM*GRIDCOLNUM  +k)* POINTSPERBIRD +3][2] = 0;
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL+GRIDCOLNUM*GRIDCOLNUM  +k)* POINTSPERBIRD +3][3] = LIGHTGRAY;
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL+GRIDCOLNUM*GRIDCOLNUM  +k)* POINTSPERBIRD +3][4] = LIGHTGRAY;
        allVertices[(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL+GRIDCOLNUM*GRIDCOLNUM  +k)* POINTSPERBIRD +3][5] = LIGHTGRAY;
        
        /*printf("%d : %f %f %f %f %f %f %f %f \n",(GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL+GRIDCOLNUM*GRIDCOLNUM + k)* POINTSPERBIRD,
         -(GRIDCOLNUM*GRIDLENGTH) + 2*GRIDLENGTH*(k%(GRIDCOLNUM-1)),
         -(GRIDCOLNUM*GRIDLENGTH) + 2*GRIDLENGTH*(k/(GRIDCOLNUM-1)),
         -(GRIDCOLNUM*GRIDLENGTH) + GRIDLENGTH+ 2*GRIDLENGTH*(k%(GRIDCOLNUM-1)),
         -(GRIDCOLNUM*GRIDLENGTH)+ 2*GRIDLENGTH*(k/(GRIDCOLNUM-1)),
         -(GRIDCOLNUM*GRIDLENGTH) + GRIDLENGTH+ 2*GRIDLENGTH*(k%(GRIDCOLNUM-1)),
         -(GRIDCOLNUM*GRIDLENGTH) + GRIDLENGTH+ 2*GRIDLENGTH*(k/(GRIDCOLNUM-1)),
         -(GRIDCOLNUM*GRIDLENGTH)+ 2*GRIDLENGTH*(k%(GRIDCOLNUM-1)),
         -(GRIDCOLNUM*GRIDLENGTH) + GRIDLENGTH+ 2*GRIDLENGTH*(k/(GRIDCOLNUM-1)));*/
    }
    
    
    //
    //
    //  set indices
    //
    //
    
    
    for (int i = 0; i< POINTSPERBIRD + GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL+SHADOWINDEXTOTAL+NUMOFGRIDSINCHECKERBOARD; i++) {
        for (int j = 0; j<VERTEXATTRIBSIZE; j++) {
            if (j<POINTSPERBIRD) {
                allElements[i][j] = i*POINTSPERBIRD+j%3;
            }else{
                allElements[i][j] = i*POINTSPERBIRD+j-2;
            }
        }
    }
    
    
    glShadeModel(GL_SMOOTH);
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    // Initialize the vertex position attribute from the vertex shader
    pos = glGetAttribLocation(program, "vPos");
    col = glGetAttribLocation(program, "vCol");
    MV = glGetUniformLocation(program, "finalview");
    
    
    // Create and initialize a buffer object
    vbo1 = make_bo(GL_ARRAY_BUFFER, allVertices, sizeof(allVertices));
    vbo2 = make_bo(GL_ELEMENT_ARRAY_BUFFER, allElements, sizeof(allElements));
    
    
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, VERTEXATTRIBSIZE * sizeof(GLfloat), (void*) 0);
    
    glEnableVertexAttribArray(col);
    glVertexAttribPointer(col, 3, GL_FLOAT, GL_FALSE, VERTEXATTRIBSIZE * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    
}


void init( void ) {
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

    // Load shaders and use the resulting shader program
    program = initshader( "example1_vs.glsl", "example1_fs.glsl" );
    glUseProgram(program);
    
    initAll();

    glClearColor( 0, 0, 0, 0 ); // white background
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


mat4 switchPersp(mat4 ProjectionMatrix, mat4 ModelViewMatrix){
    if (currentNumOfBirds > 0) {
        GLfloat tmpDist = 0;
        
        GLfloat centroidOfBoidsMass[3] = {0,0,0} ;
        GLfloat midPointOfView[3] = {0,0,0};
        GLfloat distCtoG = 0, maxDistBtoC = 0;
        GLfloat vectCtoG[3] = {0,0,0};
        
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
        
        mat4 ProjectionMatrix2  = mat4(0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0);
        mat4 ModelViewMatrix2 = mat4(0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0);
        
        switch(viewMode) {
            case DEFAULTVIEW :
                
                ProjectionMatrix2 = anotherPerspective(60.0f, 1.0f, 0.1f, 10.0f);
                ModelViewMatrix2 = anotherLookAt(vec3(0, 0, .5*VIEWSIZE), vec3(midPointOfView[0], midPointOfView[1], midPointOfView[2]), vec3(0, 0 ,1));
                
                return ModelViewMatrix2.mul(ProjectionMatrix2);
                break;
            case TRAILINGVIEW :
                
                ProjectionMatrix2 = anotherPerspective(30.0f, 1.0f, 0.1f, 20.0f);
                ModelViewMatrix2 = anotherLookAt(vec3(centroidOfBoidsMass[0] - 0.3*(distCtoG+2*maxDistBtoC)*vectCtoG[0],
                                                     centroidOfBoidsMass[1] - 0.3*(distCtoG+2*maxDistBtoC)*vectCtoG[1],
                                                     centroidOfBoidsMass[2]- 0.5*(distCtoG+2*maxDistBtoC)*vectCtoG[2] + 0.2*(distCtoG+maxDistBtoC)),
                                                vec3(midPointOfView[0], midPointOfView[1], midPointOfView[2]),
                                                vec3(0, 0 ,1));
                
                return ModelViewMatrix2.mul(ProjectionMatrix2);

                break;
            case SIDEVIEW :{
                GLfloat p[3] = {0,0,0};
                crossProd(0,0,1,  vectCtoG[0],vectCtoG[1],vectCtoG[2],  &p[0], &p[1], &p[2]);
                
                ProjectionMatrix2 = anotherPerspective(40.0f, 1.0f, 0.1f, 20.0f);
                
                ModelViewMatrix2 = anotherLookAt(vec3(midPointOfView[0] - 0.3*(distCtoG+2*maxDistBtoC)*p[0],
                                                     midPointOfView[1] - 0.3*(distCtoG+2*maxDistBtoC)*p[1],
                                                     midPointOfView[2]- 0.5*(distCtoG+5*maxDistBtoC)*p[2] + 0.2*(distCtoG + maxDistBtoC)),
                                                vec3(midPointOfView[0], midPointOfView[1], midPointOfView[2]),
                                                vec3(0, 0 ,1));
                return ModelViewMatrix2.mul(ProjectionMatrix2);
                break;
            }
            default:
                return ModelViewMatrix2.mul(ProjectionMatrix2);
                break;
        }
    }else{  // no bird on site
        mat4 ProjectionMatrix2  = mat4(0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0);
        mat4 ModelViewMatrix2 = mat4(0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0);
        
        ProjectionMatrix2 = anotherPerspective(60.0f, 1.0f, 0.1f, 20.0f);
        ModelViewMatrix2 = anotherLookAt(vec3(0, 0, VIEWSIZE),
                                        vec3(0, 0, 0),
                                        vec3(0, 1 ,0));
        
        return ModelViewMatrix2.mul(ProjectionMatrix2);
    }
}

void drawCheckBoard(mat4 inputMat){
    
    mat4 ModelViewProjectionMatrix= inputMat;
    glUniformMatrix4fv(MV, 1, false, &(ModelViewProjectionMatrix.mat4arr[0]));
    
    
    glDrawElements(GL_TRIANGLES, VERTEXATTRIBSIZE*NUMOFGRIDSINCHECKERBOARD, GL_UNSIGNED_INT, (void*)((GOALINDEXNUMTOTAL+SHADOWINDEXTOTAL+BOIDSINDEXNUMTOTAL)*VERTEXATTRIBSIZE*sizeof(GLuint)));
    
}

void drawBoid(Boid b, mat4 inputMat){
    
    
    mat4 transformM = mat4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
    
    transformM = transformM.identity4();
    transformM = transformM.mul(anotherRotatef(twoDAngle(1,0 ,b.currentVx,b.currentVy)*180/3.1415926,
                                               vec3(0,0,1)));
    transformM = transformM.mul(anotherTranslatef(vec3(b.transx,b.transy,b.transz)));
    
    mat4 ModelViewProjectionMatrix= transformM.mul(inputMat);
    
    // create and upload modelviewprojection matrix
    glUniformMatrix4fv(MV, 1, false, &(ModelViewProjectionMatrix.mat4arr[0]));
    
    glDrawElements(GL_TRIANGLES, VERTEXATTRIBSIZE, GL_UNSIGNED_INT, (void*)(GOALINDEXNUMTOTAL*VERTEXATTRIBSIZE*sizeof(GLuint)));
    //printf("\n%lu", sizeof(GLfloat));
    
}

void drawGoal(Boid b, mat4 inputMat){
    
    mat4 transformM = mat4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
    
    transformM = transformM.identity4();
    
    transformM = transformM.mul(anotherScalef(vec3(1,1,1)));
    transformM = transformM.mul(anotherRotatef(twoDAngle(1,0 ,b.currentVx,b.currentVy)*180/3.1415926,
                                               vec3(0,0,1)));
    //printf("%f, %f, %f", b.transx,b.transy,b.transz);
    
    transformM = transformM.mul(anotherTranslatef(vec3(b.transx,b.transy,b.transz)));
    
    mat4 ModelViewProjectionMatrix = transformM.mul(inputMat);
    
    // create and upload modelviewprojection matrix
    glUniformMatrix4fv(MV, 1, false, &(ModelViewProjectionMatrix.mat4arr[0]));
    
    //glUniformMatrix4fv(MV, 1, GL_FALSE, transformM.mat4arr);
    glDrawElements(GL_TRIANGLES, VERTEXATTRIBSIZE, GL_UNSIGNED_INT, 0);
}

void drawShadow(Boid b, mat4 inputMat){
    
    mat4 transformM = mat4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
    
    transformM = transformM.identity4();
    
    transformM = transformM.mul(anotherScalef(vec3(1,1,1)));
    transformM = transformM.mul(anotherRotatef(twoDAngle(1,0 ,b.currentVx,b.currentVy)*180/3.1415926,
                                               vec3(0,0,1)));
    //printf("%f, %f, %f", b.transx,b.transy,b.transz);
    
    transformM = transformM.mul(anotherTranslatef(vec3(b.transx,b.transy, 0.01)));
    
    mat4 ModelViewProjectionMatrix = transformM.mul(inputMat);
    
    // create and upload modelviewprojection matrix
    glUniformMatrix4fv(MV, 1, false, &(ModelViewProjectionMatrix.mat4arr[0]));
    
    //glUniformMatrix4fv(MV, 1, GL_FALSE, transformM.mat4arr);
    glDrawElements(GL_TRIANGLES, VERTEXATTRIBSIZE, GL_UNSIGNED_INT, (void*)((GOALINDEXNUMTOTAL+BOIDSINDEXNUMTOTAL)*VERTEXATTRIBSIZE*sizeof(GLuint)));
}



void update(){
    updateKeyboard();
    
    realTimeCount ++;
    if (realTimeCount == 3600) {
        realTimeCount = 0;
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
        
        if (leftPress == TRUE || rightPress == TRUE) {
            GLfloat v1, v2, v3;
            
            if(leftPress == TRUE)
                crossProd(boids[GOALINDEX].lastX1,boids[GOALINDEX].lastY1,0,  0,0,-1,  &v1, &v2, &v3);
            
            if(rightPress == TRUE)
                crossProd(boids[GOALINDEX].lastX1,boids[GOALINDEX].lastY1,0,  0,0,1,  &v1, &v2, &v3);
            
            GLfloat directionX = v1;
            GLfloat directionY = v2;
            GLfloat directionZ = 0;
            
            normalizeVec(&directionX, &directionY, &directionZ);
            
            boids[GOALINDEX].currentVx += TURNINGSPPED * directionX;
            boids[GOALINDEX].currentVy += TURNINGSPPED * directionY;
            
            leftPress = FALSE;
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
        }else if(constForVelocity < 0.1){
            constForVelocity = 0.1;
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
}



void updateKeyboard(){
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
}

int main(int argc, char **argv) {
    // start GL context and O/S window using the GLFW helper library
    if (!glfwInit ()) {
        fprintf (stderr, "ERROR: could not start GLFW3\n");
        return 1;
    }
    
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow *window = glfwCreateWindow (512, 512, "hw4", NULL, NULL);
    if (!window) {
        fprintf (stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent (window);
    
    // Assign reshape() to be the function called whenever
    // a reshape event occurs
    glfwSetFramebufferSizeCallback(window, reshape);
    
    // will segfault otherwise in init()
    glewExperimental = GL_TRUE;
    glewInit();
    
    printf("%s\n", glGetString(GL_VERSION));
    
    init();
    glfwSetKeyCallback(window, keyboard);
    
    while (!glfwWindowShouldClose (window)) {
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // draw the points
        draw();
        glfwSwapBuffers (window);
        // update other events like input handling
        glfwPollEvents ();
    }
    
    glfwTerminate();
    return 0;
}
