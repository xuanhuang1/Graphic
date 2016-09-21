/*
        Homework1 CS312
        Xuan Huang
        Tue Sep 6, 2016
 
*/





#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>

struct node {
    GLint type;  //Basic 0 poly 1
    void* data;
    struct node *next;
};
typedef struct node Node;
// typedef Node *Nodeptr;

typedef struct {
    GLint shape; //F1 Line; F2 Poly; F3 rect; F4 cir;
    GLint f;     // 0 noFill; 1 Fill
    GLint r;
    GLint g;
    GLint b;
    GLdouble x1;
    GLdouble y1;
    GLdouble x2;
    GLdouble y2;
    GLdouble x3;
    GLdouble y3;
} Basic;

typedef struct {
    GLdouble data;
} Poly;



Basic *make_Basic( GLint shape, GLint f, GLint r, GLint g, GLint b, GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2, GLdouble x3, GLdouble y3){
    Basic *newN;
    if ( (newN = (Basic *) malloc( sizeof(Basic) ) )!= 0) {
        newN->shape =  shape;
        newN->f =  f;
        newN->r =  r;
        newN->g =  g;
        newN->b =  b;
        newN->x1 =  x1;
        newN->x2 =  x2;
        newN->y1 =  y1;
        newN->y2 =  y2;
        newN->x3 =  x3;
        newN->y3 =  y3;
    }
    else {
        printf("Out of memory!\n");
        exit(0);
    }
    return newN;
}

Poly *make_Poly(GLdouble x){
    Poly *newN;
    if ( (newN = (Poly *) malloc( sizeof(Poly) ) )!= 0) {
        newN->data =  x;
    }
    else {
        printf("Out of memory!\n");
        exit(0);
    }
    return newN;
}



/************ Head and Tail *****************/
/************ node setting *****************/


Node *head = 0;
Node *tail = 0;

Node *makenode (GLint tp, void* x) {
    Node *newN;
    if ( (newN = (Node *) malloc( sizeof(Node) ) )!= 0) {
        newN->data =  x;
        newN-> next = 0;
        newN->type = tp;
    }
    else {
        printf("Out of memory!\n");
        exit(0);
    }
    return newN;
}

void add (Node *p) {
    if (head == 0) {
        head = p;
        tail = p;
    }
    else {
        tail->next = p;
        tail = p;
    }
}


void clear() {
    Node *tmp, *tmp2;
    for (tmp = head; tmp != NULL; tmp = tmp2) {
        tmp2 = tmp->next;
        free(tmp->data);
        free(tmp);
    }
    head = tail = NULL;
}

//                   //
//                   //
// varibles declare  //
//                   //
//                   //


GLint shapeMode; // 0 basic 1 polyon
GLint drawshape; // 1 LINE, 2 TRIAN 3 RECT 4 CIR
GLint fillF, colorR, colorG, colorB, cClear;  // f: fill r, g, b, c:clear, q/Q/escape: quit
GLint keyHold, mouseHold, cursorMove, indexOfTrian;
GLdouble mouseX, mouseY, mouse2X, mouse2Y, mouse3X, mouse3Y, mouseCX, mouseCY;
GLdouble widC = 400;
GLdouble heiC = 400;
GLdouble cr = 0, cb= 0, cg= 0;


void init() {
    //shape default, basic shape
    shapeMode = 0;
    
    //drawshape default, line
    drawshape = 1;
    
    //mouse is not held
    mouseHold = 0;
    
    //stroke weight
    glLineWidth(3);
    
    // Set the clear color to black
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    //set camera to canvas size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, widC, 0.0 ,heiC);
    glMatrixMode(GL_MODELVIEW);
    
}

void draw(){
    glClear(GL_COLOR_BUFFER_BIT);
    
    
    Node *tmp, *tmp2;
    
    
    
    //draw everything in the linked list
    for (tmp = head; tmp != NULL; tmp = tmp2) {
        tmp2 = tmp->next;

        
        if (tmp->type == 0) { // Basic type
            glColor3f( ((Basic*)tmp->data)->r, ((Basic*)tmp->data)->g, ((Basic*)tmp->data)->b);

            if(((Basic*)tmp->data)->f == 0){  // no fill
                switch (((Basic*)tmp->data)->shape) {
                    case 0:
                        break;
                    case 1:// LINE

                        glBegin(GL_LINE_STRIP);
                        glVertex2f(((Basic*)tmp->data)->x1, ((Basic*)tmp->data)->y1);
                        glVertex2f(((Basic*)tmp->data)->x2, ((Basic*)tmp->data)->y2);
                        glEnd();
                        break;
                    case 2: // TRIANGLE
                        glBegin(GL_LINE_LOOP);
                        glVertex2f(((Basic*)tmp->data)->x1, ((Basic*)tmp->data)->y1);
                        glVertex2f(((Basic*)tmp->data)->x2, ((Basic*)tmp->data)->y2);
                        glVertex2f(((Basic*)tmp->data)->x3, ((Basic*)tmp->data)->y3);
                        glEnd();
                        break;
                        glEnd();
                        break;
                    case 3: // RECTANGLE
                        glBegin(GL_LINE_LOOP);
                        glVertex2f(((Basic*)tmp->data)->x1, ((Basic*)tmp->data)->y1);
                        glVertex2f(((Basic*)tmp->data)->x1, ((Basic*)tmp->data)->y2);
                        glVertex2f(((Basic*)tmp->data)->x2, ((Basic*)tmp->data)->y2);
                        glVertex2f(((Basic*)tmp->data)->x2, ((Basic*)tmp->data)->y1);
                        glEnd();
                        break;
                    case 4: //CIRCLE
                    {
                        
                        GLdouble radius = sqrt( pow((((Basic*)tmp->data)->x1-((Basic*)tmp->data)->x2), 2)+ pow((((Basic*)tmp->data)->y1-((Basic*)tmp->data)->y2), 2) );
                        GLdouble pi = 3.1415916;
                        
                        glBegin(GL_LINE_LOOP);
                        for (GLint i =0; i<200; i++) {
                            glVertex2f(((Basic*)tmp->data)->x1 + sin( 2*pi*i/200)*radius, ((Basic*)tmp->data)->y1+ cos( 2*pi*i/200)*radius);
                        }
                        glEnd();
                        break;
                    }
                    default:
                        break;
                }
                
            }else if(((Basic*)tmp->data)->f == 1){ // fill mode
                switch (((Basic*)tmp->data)->shape) {
                    case 0:
                        break;
                    case 1:
                        glBegin(GL_LINE_STRIP);
                        glVertex2f(((Basic*)tmp->data)->x1, ((Basic*)tmp->data)->y1);
                        glVertex2f(((Basic*)tmp->data)->x2, ((Basic*)tmp->data)->y2);
                        glEnd();
                        break;
                    case 2:
                        glBegin(GL_POLYGON);
                        glVertex2f(((Basic*)tmp->data)->x1, ((Basic*)tmp->data)->y1);
                        glVertex2f(((Basic*)tmp->data)->x2, ((Basic*)tmp->data)->y2);
                        glVertex2f(((Basic*)tmp->data)->x3, ((Basic*)tmp->data)->y3);
                        glEnd();
                        break;
                    case 3:
                        glBegin(GL_POLYGON);
                        glVertex2f(((Basic*)tmp->data)->x1, ((Basic*)tmp->data)->y1);
                        glVertex2f(((Basic*)tmp->data)->x1, ((Basic*)tmp->data)->y2);
                        glVertex2f(((Basic*)tmp->data)->x2, ((Basic*)tmp->data)->y2);
                        glVertex2f(((Basic*)tmp->data)->x2, ((Basic*)tmp->data)->y1);
                        glEnd();
                        break;
                    case 4:
                    {
                        GLdouble radius = sqrt( pow((((Basic*)tmp->data)->x1-((Basic*)tmp->data)->x2), 2)+ pow((((Basic*)tmp->data)->y1-((Basic*)tmp->data)->y2), 2) );
                        GLdouble pi = 3.1415916;
                        
                        glBegin(GL_POLYGON);
                        for (GLint i =0; i<200; i++) {
                            glVertex2f(((Basic*)tmp->data)->x1 + sin( 2*pi*i/200)*radius, ((Basic*)tmp->data)->y1+ cos( 2*pi*i/200)*radius);
                        }
                        glEnd();
                        break;
                    }
                    default:
                        break;
                }
            }
            
            
        }else if(tmp->type == 1){ // polygon
            
        }
        
        
    }
    
    
    //rubberband
    
    if (cursorMove) {
        if (shapeMode == 0 && drawshape == 1) {  // LINE
            glColor3f(colorR % 2,colorG % 2,colorB % 2);
            GLdouble cWid = mouseX, cHei = mouseY;
            
            glBegin(GL_POLYGON);
            glVertex2f(cWid + 2, cHei + 2);
            glVertex2f(cWid - 2, cHei + 2);
            glVertex2f(cWid - 2, cHei - 2);
            glVertex2f(cWid + 2, cHei - 2);
            glEnd();
            
            for (GLint i=0; i<32; i+=2) {
                glBegin(GL_LINE_STRIP);
                glVertex2f(cWid + i*(mouse2X-cWid)/31, cHei + i*(mouse2Y-cHei)/31);
                glVertex2f(cWid + (i+1)*(mouse2X-cWid)/31, cHei + (i+1)*(mouse2Y-cHei)/31);
                glEnd();
            }
            
            glBegin(GL_POLYGON);
            glVertex2f(mouse2X + 2, mouse2Y + 2);
            glVertex2f(mouse2X - 2, mouse2Y + 2);
            glVertex2f(mouse2X - 2, mouse2Y - 2);
            glVertex2f(mouse2X + 2, mouse2Y - 2);
            glEnd();
            
        }else if (shapeMode == 0 && drawshape == 2) { // TRIANGLE
            glColor3f(colorR % 2,colorG % 2,colorB % 2);
            if (indexOfTrian % 3  == 2) {  // last vertex comfirm
                GLdouble cWid = mouseX, cHei = mouseY;
                
                //first line 1-2
                
                glBegin(GL_POLYGON);
                glVertex2f(cWid + 2, cHei + 2);
                glVertex2f(cWid - 2, cHei + 2);
                glVertex2f(cWid - 2, cHei - 2);
                glVertex2f(cWid + 2, cHei - 2);
                glEnd();
                
                for (GLint i=0; i<32; i+=2) {
                    
                    glBegin(GL_LINE_STRIP);
                    glVertex2f(cWid + i*(mouse2X-cWid)/31, cHei + i*(mouse2Y-cHei)/31);
                    glVertex2f(cWid + (i+1)*(mouse2X-cWid)/31, cHei + (i+1)*(mouse2Y-cHei)/31);
                    glEnd();
                    
                }
                
                glBegin(GL_POLYGON);
                glVertex2f(mouse2X + 2, mouse2Y + 2);
                glVertex2f(mouse2X - 2, mouse2Y + 2);
                glVertex2f(mouse2X - 2, mouse2Y - 2);
                glVertex2f(mouse2X + 2, mouse2Y - 2);
                glEnd();
                
                
                // second line 2-3
                cWid = mouse2X, cHei = mouse2Y;
                
                glBegin(GL_POLYGON);
                glVertex2f(cWid + 2, cHei + 2);
                glVertex2f(cWid - 2, cHei + 2);
                glVertex2f(cWid - 2, cHei - 2);
                glVertex2f(cWid + 2, cHei - 2);
                glEnd();
                
                for (GLint i=0; i<32; i+=2) {
                    
                    glBegin(GL_LINE_STRIP);
                    glVertex2f(cWid + i*(mouseCX-cWid)/31, cHei + i*(mouseCY-cHei)/31);
                    glVertex2f(cWid + (i+1)*(mouseCX-cWid)/31, cHei + (i+1)*(mouseCY-cHei)/31);
                    glEnd();

                }
                
                glBegin(GL_POLYGON);
                glVertex2f(mouseCX + 2, mouseCY + 2);
                glVertex2f(mouseCX - 2, mouseCY + 2);
                glVertex2f(mouseCX - 2, mouseCY - 2);
                glVertex2f(mouseCX + 2, mouseCY - 2);
                glEnd();
                
                //third line 3-1
                cWid = mouseCX, cHei = mouseCY;
                
                glBegin(GL_POLYGON);
                glVertex2f(cWid + 2, cHei + 2);
                glVertex2f(cWid - 2, cHei + 2);
                glVertex2f(cWid - 2, cHei - 2);
                glVertex2f(cWid + 2, cHei - 2);
                glEnd();
                
                for (GLint i=0; i<32; i+=2) {
                    
                    glBegin(GL_LINE_STRIP);
                    glVertex2f(cWid + i*(mouseX-cWid)/31, cHei + i*(mouseY-cHei)/31);
                    glVertex2f(cWid + (i+1)*(mouseX-cWid)/31, cHei + (i+1)*(mouseY-cHei)/31);
                    glEnd();

                }
                
                glBegin(GL_POLYGON);
                glVertex2f(mouseX + 2, mouseY + 2);
                glVertex2f(mouseX - 2, mouseY + 2);
                glVertex2f(mouseX - 2, mouseY - 2);
                glVertex2f(mouseX + 2, mouseY - 2);
                glEnd();
                
            }else if (indexOfTrian % 3  == 0){ // no vertex set/ last vertex set
                
                cursorMove = 0;
                
                glBegin(GL_POLYGON);
                glVertex2f(mouseCX + 2, mouseCY + 2);
                glVertex2f(mouseCX - 2, mouseCY + 2);
                glVertex2f(mouseCX - 2, mouseCY - 2);
                glVertex2f(mouseCX + 2, mouseCY - 2);
                glEnd();

                
            }else if (indexOfTrian % 3  == 1){ // set second vertex
                
                GLdouble cWid = mouseX, cHei = mouseY;
                
                glBegin(GL_POLYGON);
                glVertex2f(cWid + 2, cHei + 2);
                glVertex2f(cWid - 2, cHei + 2);
                glVertex2f(cWid - 2, cHei - 2);
                glVertex2f(cWid + 2, cHei - 2);
                glEnd();
                
                for (GLint i=0; i<32; i+=2) {

                    glBegin(GL_LINE_STRIP);
                    glVertex2f(cWid + i*(mouseCX-cWid)/31, cHei + i*(mouseCY-cHei)/31);
                    glVertex2f(cWid + (i+1)*(mouseCX-cWid)/31, cHei + (i+1)*(mouseCY-cHei)/31);
                    glEnd();

                }
                
                glBegin(GL_POLYGON);
                glVertex2f(mouseCX + 2, mouseCY + 2);
                glVertex2f(mouseCX - 2, mouseCY + 2);
                glVertex2f(mouseCX - 2, mouseCY - 2);
                glVertex2f(mouseCX + 2, mouseCY - 2);
                glEnd();
            }
            
            
            
        }else if (shapeMode == 0 && drawshape == 3) { //RECT
            GLdouble cWid = mouseX, cHei = mouseY;
            glColor3f(colorR % 2,colorG % 2,colorB % 2);
            
            
            glBegin(GL_POLYGON);
            glVertex2f(cWid + 2, cHei + 2);
            glVertex2f(cWid - 2, cHei + 2);
            glVertex2f(cWid - 2, cHei - 2);
            glVertex2f(cWid + 2, cHei - 2);
            glEnd();
            
            for (GLint i=0; i<32; i+=2) {
                glBegin(GL_LINE_STRIP);
                glVertex2f(cWid + i*(mouse2X-cWid)/31, mouse2Y);
                glVertex2f(cWid + (i+1)*(mouse2X-cWid)/31, mouse2Y);
                glEnd();
            }
            
            glBegin(GL_POLYGON);
            glVertex2f(mouse2X + 2, mouse2Y + 2);
            glVertex2f(mouse2X - 2, mouse2Y + 2);
            glVertex2f(mouse2X - 2, mouse2Y - 2);
            glVertex2f(mouse2X + 2, mouse2Y - 2);
            glEnd();
            
            for (GLint i=0; i<32; i+=2) {
                glBegin(GL_LINE_STRIP);
                glVertex2f(cWid + i*(mouse2X-cWid)/31, mouseY);
                glVertex2f(cWid + (i+1)*(mouse2X-cWid)/31, mouseY);
                glEnd();
            }
            
            glBegin(GL_POLYGON);
            glVertex2f(mouseX + 2, mouse2Y + 2);
            glVertex2f(mouseX - 2, mouse2Y + 2);
            glVertex2f(mouseX - 2, mouse2Y - 2);
            glVertex2f(mouseX + 2, mouse2Y - 2);
            glEnd();
            
            for (GLint i=0; i<32; i+=2) {
                glBegin(GL_LINE_STRIP);
                glVertex2f(mouseX, cHei+i*(mouse2Y-cHei)/31);
                glVertex2f(mouseX, cHei+(i+1)*(mouse2Y-cHei)/31);
                glEnd();
            }
            
            glBegin(GL_POLYGON);
            glVertex2f(mouse2X + 2, mouseY + 2);
            glVertex2f(mouse2X - 2, mouseY + 2);
            glVertex2f(mouse2X - 2, mouseY - 2);
            glVertex2f(mouse2X + 2, mouseY - 2);
            glEnd();
            
            for (GLint i=0; i<32; i+=2) {
                glBegin(GL_LINE_STRIP);
                glVertex2f(mouse2X, cHei+i*(mouse2Y-cHei)/31);
                glVertex2f(mouse2X, cHei+(i+1)*(mouse2Y-cHei)/31);
                glEnd();
            }
            
            
        }else if (shapeMode == 0 && drawshape == 4) {
            
            glColor3f(colorR % 2,colorG % 2,colorB % 2);
            GLdouble radius = sqrt( pow(mouseX-mouse2X, 2)+ pow(mouseY-mouse2Y, 2) );
            GLdouble pi = 3.1415916;
            
            glBegin(GL_POLYGON);
            glVertex2f(mouse2X + 2, mouse2Y + 2);
            glVertex2f(mouse2X - 2, mouse2Y + 2);
            glVertex2f(mouse2X - 2, mouse2Y - 2);
            glVertex2f(mouse2X + 2, mouse2Y - 2);
            glEnd();
            
            glBegin(GL_POLYGON);
            glVertex2f(mouseX + 2, mouseY + 2);
            glVertex2f(mouseX - 2, mouseY + 2);
            glVertex2f(mouseX - 2, mouseY - 2);
            glVertex2f(mouseX + 2, mouseY - 2);
            glEnd();
            
            for (GLint i=0; i<100; i+=2) {
                glBegin(GL_LINE_STRIP);
                glVertex2f(mouseX + sin( 2*pi*i/100)*radius, mouseY+ cos( 2*pi*i/100)*radius);
                glVertex2f(mouseX + sin( 2*pi*(i+1)/100)*radius, mouseY+ cos( 2*pi*(i+1)/100)*radius);
                glEnd();
            }
            
            
        }else{
            
        }
    }
    
}

void mouse(GLFWwindow* window, GLint button, GLint action, GLint mods) {
    GLdouble xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    if(shapeMode ==0 && drawshape == 2){
        Node *tmp;
        switch (button) {
            case GLFW_MOUSE_BUTTON_LEFT:
                //printf("left\n");
                if (action==GLFW_PRESS) {
                    switch (indexOfTrian % 3){
                        case 0:
                            mouseX = xpos;
                            mouseY = -ypos+heiC;
                            break;
                        case 1:
                            mouse2X = xpos;
                            mouse2Y = -ypos+heiC;
                            break;
                        case 2:
                
                            mouse3X = xpos;
                            mouse3Y = -ypos+heiC;
                            Basic* ip = make_Basic(drawshape, fillF % 2, colorR % 2, colorG % 2, colorB % 2, mouseX, mouseY, mouse2X, mouse2Y, mouse3X, mouse3Y );
                            tmp = makenode(0, ip);
                            add(tmp);
                            //printf("Got a shape %d %d %d %d %d %f %f %f %f %f %f\n", drawshape, fillF % 2, colorR % 2, colorG % 2, colorB % 2, mouseX, mouseY, mouse2X, mouse2Y, mouse3X, mouse3Y);
                            break;
                            
                    }
                    indexOfTrian++;
                }
                break;
                
            default :
                printf("none\n");
                break;
        }
        
        
    }else{
        
        
        switch (button) {
            case GLFW_MOUSE_BUTTON_LEFT:
                //printf("left\n");
                if (action==GLFW_PRESS) {
                    
                    mouseHold = 1;
                    mouseX = xpos;
                    mouseY = -ypos+heiC;

                }else{
                    mouseHold = 2;
                    Node *tmp;
                    mouse2X = xpos;
                    mouse2Y = -ypos+heiC;
                    //mouseHold = 0;
                    switch (shapeMode) {
                        case 0:
                        {
                            Basic* ip = make_Basic(drawshape, fillF % 2, colorR % 2, colorG % 2, colorB % 2, mouseX, mouseY, mouse2X, mouse2Y, mouse3X, mouse3Y);
                            tmp = makenode(0, ip);
                            add(tmp);
                            printf("A shape added\n");
                            break;
                        }
                        default:
                            break;
                    }
                    
                }
                break;
            case GLFW_MOUSE_BUTTON_RIGHT:
                printf("right\n");
                break;
            case GLFW_MOUSE_BUTTON_MIDDLE:
                printf("MIDDLE\n");
                break;
            default :
                printf("none\n");
                break;
        }
    }
}

void cursor(GLFWwindow* window, GLdouble xpos, GLdouble ypos) {
    if (drawshape == 2 && shapeMode ==0) {
        if (indexOfTrian % 3 != 0) {
            cursorMove = 1;
        }
        glfwGetCursorPos(window, &mouseCX, &mouseCY);
        mouseCY = heiC -mouseCY;

        
    }else{
        
        if (mouseHold == 1) {
            cursorMove = 1;
            glfwGetCursorPos(window, &mouse2X, &mouse2Y);
            mouse2Y = heiC - mouse2Y;
        }else if(mouseHold == 2){
            cursorMove = 0;
            mouseHold = 0;
        }
    }
}

void keyboard(GLFWwindow *w, GLint key, GLint scancode, GLint action, GLint mods) {
    //printf("Got a Keyboard Event: ");
    //printf(" %d, ", key);
    
    switch(action) {
        case GLFW_PRESS :
            keyHold = 1;
            //printf("pressed,\t");
            break;
        case GLFW_RELEASE :
            keyHold = 0;
            //printf("released,\t");
            break;
        case GLFW_REPEAT :
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
        case 'Q' :
            glfwSetWindowShouldClose(w, GL_TRUE);
            break;
        case 'f' :
        case 'F':
            if(keyHold){
                fillF++;
                printf("Change filling mode %s", fillF%2 == 0?"no Fill\n":"Fill\n");
            }
            break;
        case 'r' :
        case 'R' :
            if(keyHold){
                colorR++;
                printf("Change filling mode %s", colorR%2 == 0?"no Red\n":"with Red\n");
            }
            break;
        case 'g' :
        case 'G' :
            if(keyHold){
                colorG++;
                printf("Change filling mode %s", colorG%2 == 0?"no Green\n":"with Green\n");
            }
            break;
        case 'b' :
        case 'B' :
            if(keyHold){
                colorB++;
                printf("Change filling mode %s", colorB%2 == 0?"no Blue\n":"with Blue\n");
            }
            break;
        case 'c' :
        case 'C' :
            clear();
            printf("Clear board\n");
            break;
            
            
        case GLFW_KEY_F1 :
            drawshape =1;
            mouseX = 0;
            mouseY = 0;
            mouse2X = 0;
            mouse2Y = 0;
            mouse3X = 0;
            mouse3Y = 0;
            printf("Drawing in LINE mode\n");
            break;
        case GLFW_KEY_F2 :
            drawshape =2;
            mouseX = 0;
            mouseY = 0;
            mouse2X = 0;
            mouse2Y = 0;
            mouse3X = 0;
            mouse3Y = 0;
            printf("Drawing in TRIANGLE mode\n");
            break;
        case GLFW_KEY_F3 :
            drawshape =3;
            mouseX = 0;
            mouseY = 0;
            mouse2X = 0;
            mouse2Y = 0;
            mouse3X = 0;
            mouse3Y = 0;
            printf("Drawing in RECTANGLE mode\n");
            break;
        case GLFW_KEY_F4 :
            drawshape =4;
            mouseX = 0;
            mouseY = 0;
            mouse2X = 0;
            mouse2Y = 0;
            mouse3X = 0;
            mouse3Y = 0;
            printf("Drawing in CIRCLE mode\n");
            break;
        default:
            break;
    }
}

void framebuffer_resize(GLFWwindow* w, GLint width, GLint height){
    glViewport(0, 0, width, height);
}

GLint main (GLint argc, char** argv){
    GLFWwindow* w;
    
    if (!glfwInit())
        exit(EXIT_FAILURE);
    
    w = glfwCreateWindow(widC, heiC, "simple", NULL, NULL);
    
    if (!w){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    glfwSetWindowPos(w, 800, 500);
    
    // Make the window's context current
    glfwMakeContextCurrent(w);
    
    glfwSetFramebufferSizeCallback(w, framebuffer_resize);
    glfwSetMouseButtonCallback(w, mouse);
    
    // Assign keyboard() to be the function called whenever
    // a key is pressed or released
    glfwSetKeyCallback(w, keyboard);
    
    // Assign cursor() to be the function called whenever
    // a cursor moves
    glfwSetCursorPosCallback(w, cursor);
    
    glfwSetWindowSize(w, widC, heiC);
    
    init();
    
    
    
    while(!glfwWindowShouldClose(w)){
        draw();
        glfwSwapBuffers(w);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
    
}
