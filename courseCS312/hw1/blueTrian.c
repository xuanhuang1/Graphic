#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>

struct node {
    int type;  //Basic 0 poly 1
    void* data;
    struct node *next;
};
typedef struct node Node;
// typedef Node *Nodeptr;

typedef struct {
    int shape; //F1 Line; F2 Poly; F3 rect; F4 cir;
    int f;     // 0 noFill; 1 Fill
    int r;
    int g;
    int b;
    double x1;
    double y1;
    double x2;
    double y2;
    double x3;
    double y3;
} Basic;

typedef struct {
    double data;
} Poly;



Basic *make_Basic( int shape, int f, int r, int g, int b, double x1, double y1, double x2, double y2, double x3, double y3){
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

Poly *make_Poly(double x){
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

Node *makenode (int tp, void* x) {
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

void delete (Node *p) {
    Node *tmp, *prev;
    if ((p == head) && (p == tail)) {
        head = tail = 0;
    }
    else if (p == head) {
        head = p->next;
    }
    else {
        for(tmp=head, prev=0; tmp!=p; prev=tmp, tmp=tmp->next);
        if (p == tail)
            tail = prev;
        prev->next = p->next;
        
    }
}

void print() {
    Node *tmp;
    for (tmp = head; tmp != 0; tmp = tmp->next) {
        if(tmp->type == 1){
            //printf("%d is Basic;", ((Basic*)tmp->data)->shape);
        }else if(tmp->type == 2){
            //printf("%d is Poly;", ((Poly*)tmp->data)->shape);
        }
        printf("\n");
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


int shapeMode; // 0 basic 1 poly
int drawshape; // 1 LINE, 2 TRIAN 3 RECT 4 CIR
int fillF, colorR, colorG, colorB, cClear;  // f: fill r, g, b, c:clear, q/Q/escape: quit
int keyHold, mouseHold, cursorMove, indexOfTrian;
double mouseX, mouseY, mouse2X, mouse2Y, mouse3X, mouse3Y, mouseCX, mouseCY;
double widC = 400;
double heiC = 400;
double cr = 0, cb= 0, cg= 0;


void init() {
    // Set the clear color to black
    shapeMode = 0;
    drawshape = 1;
    mouseHold = 0;
    glClearColor(1.0, 1.0, 1.0, 1.0);
    //glColor3f(0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, widC, 0.0 ,heiC);
    glMatrixMode(GL_MODELVIEW);
    
}

void draw(){
    glClear(GL_COLOR_BUFFER_BIT);
    
    
    Node *tmp, *tmp2;
    for (tmp = head; tmp != NULL; tmp = tmp2) {
        tmp2 = tmp->next;
        //printf("showlist in mode basic/poly: %d \n", tmp->type);
        
        if (tmp->type == 0) {
            glColor3f( ((Basic*)tmp->data)->r, ((Basic*)tmp->data)->g, ((Basic*)tmp->data)->b);
            //printf("showlist in shape(n-gon): %d \n", ((Basic*)tmp->data)->shape);
            if(((Basic*)tmp->data)->f == 0){
                switch (((Basic*)tmp->data)->shape) {
                    case 0:
                        break;
                    case 1:
                        //printf("vertices prev: %f, %f ", ((Basic*)tmp->data)->x1, ((Basic*)tmp->data)->y1);
                        //printf("vertices cur: %f, %f ", ((Basic*)tmp->data)->x2, ((Basic*)tmp->data)->y2);
                        glBegin(GL_LINE_STRIP);
                        glVertex2f(((Basic*)tmp->data)->x1, ((Basic*)tmp->data)->y1);
                        glVertex2f(((Basic*)tmp->data)->x2, ((Basic*)tmp->data)->y2);
                        glEnd();
                        break;
                    case 2:
                        glBegin(GL_LINE_LOOP);
                        glVertex2f(((Basic*)tmp->data)->x1, ((Basic*)tmp->data)->y1);
                        glVertex2f(((Basic*)tmp->data)->x2, ((Basic*)tmp->data)->y2);
                        glVertex2f(((Basic*)tmp->data)->x3, ((Basic*)tmp->data)->y3);
                        glEnd();
                        break;
                        glEnd();
                        break;
                    case 3:
                        glBegin(GL_LINE_LOOP);
                        glVertex2f(((Basic*)tmp->data)->x1, ((Basic*)tmp->data)->y1);
                        glVertex2f(((Basic*)tmp->data)->x1, ((Basic*)tmp->data)->y2);
                        glVertex2f(((Basic*)tmp->data)->x2, ((Basic*)tmp->data)->y2);
                        glVertex2f(((Basic*)tmp->data)->x2, ((Basic*)tmp->data)->y1);
                        glEnd();
                        break;
                    case 4:
                    {
                        
                        double radius = sqrt( pow((((Basic*)tmp->data)->x1-((Basic*)tmp->data)->x2), 2)+ pow((((Basic*)tmp->data)->y1-((Basic*)tmp->data)->y2), 2) );
                        double pi = 3.1415916;
                        
                        glBegin(GL_LINE_LOOP);
                        for (int i =0; i<200; i++) {
                            glVertex2f(((Basic*)tmp->data)->x1 + sin( 2*pi*i/200)*radius, ((Basic*)tmp->data)->y1+ cos( 2*pi*i/200)*radius);
                        }
                        glEnd();
                        break;
                    }
                    default:
                        break;
                }
                
            }else if(((Basic*)tmp->data)->f == 1){
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
                        double radius = sqrt( pow((((Basic*)tmp->data)->x1-((Basic*)tmp->data)->x2), 2)+ pow((((Basic*)tmp->data)->y1-((Basic*)tmp->data)->y2), 2) );
                        double pi = 3.1415916;
                        
                        glBegin(GL_POLYGON);
                        for (int i =0; i<200; i++) {
                            glVertex2f(((Basic*)tmp->data)->x1 + sin( 2*pi*i/200)*radius, ((Basic*)tmp->data)->y1+ cos( 2*pi*i/200)*radius);
                        }
                        glEnd();
                        break;
                    }
                    default:
                        break;
                }
            }
            
            
        }else if(tmp->type == 1){
            
        }
        
        
    }
    //rubberbound
    
    
    if (cursorMove) {
        if (shapeMode == 0 && drawshape == 1) {
            glColor3f(0,0,1);
            glBegin(GL_LINE_STRIP);
            glVertex2f(mouseX, mouseY);
            glVertex2f(mouse2X, mouse2Y);
            glEnd();
        }else if (shapeMode == 0 && drawshape == 2) {
            glColor3f(0,0,1);
            if (indexOfTrian % 3  == 2) {
                glBegin(GL_LINE_LOOP);
                glVertex2f(mouseX, mouseY);
                glVertex2f(mouseCX, mouseCY);
                glVertex2f(mouse2X, mouse2Y);
                glEnd();
            }else if (indexOfTrian % 3  == 0){
                
                cursorMove = 0;
                //trianOn = 0;
                
            }else if (indexOfTrian % 3  == 1){
                
                glBegin(GL_LINE_STRIP);
                glVertex2f(mouseX, mouseY);
                glVertex2f(mouseCX, mouseCY);
                glEnd();
            }
            
            
            
        }else if (shapeMode == 0 && drawshape == 3) {
            
            glColor3f(0,0,1);
            glBegin(GL_LINE_LOOP);
            glVertex2f(mouseX, mouseY);
            glVertex2f(mouseX, mouse2Y);
            glVertex2f(mouse2X, mouse2Y);
            glVertex2f(mouse2X, mouseY);
            glEnd();
            //mouseHold = 0;
            
            
            
        }else if (shapeMode == 0 && drawshape == 4) {
            
            glColor3f(0,0,1);
            double radius = sqrt( pow(mouseX-mouse2X, 2)+ pow(mouseY-mouse2Y, 2) );
            double pi = 3.1415916;
            
            glBegin(GL_LINE_LOOP);
            for (int i =0; i<200; i++) {
                glVertex2f(mouseX + sin( 2*pi*i/200)*radius, mouseY+ cos( 2*pi*i/200)*radius);
            }
            glEnd();
            
            
        }else{
            
        }
    }
    
}

void mouse(GLFWwindow* window, int button, int action, int mods) {
    double xpos, ypos;
    printf("Got a Mouse %s Event", action==GLFW_PRESS?"press":"release");
    glfwGetCursorPos(window, &xpos, &ypos);
    printf(":\t x = %f, y = %f, button = ", xpos, ypos);
    if(shapeMode ==0 && drawshape == 2){
        Node *tmp;
        switch (button) {
            case GLFW_MOUSE_BUTTON_LEFT:
                printf("left\n");
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
                            printf("Got a shape %d %d %d %d %d %f %f %f %f %f %f\n", drawshape, fillF % 2, colorR % 2, colorG % 2, colorB % 2, mouseX, mouseY, mouse2X, mouse2Y, mouse3X, mouse3Y);
                            break;
                            
                    }
                    printf("index++\n");
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
                printf("left\n");
                if (action==GLFW_PRESS) {
                    
                    mouseHold = 1;
                    mouseX = xpos;
                    mouseY = -ypos+heiC;
                    printf("Got a Mouse %s Event INSIDE CASE", action==GLFW_PRESS?"press":"release");
                    printf(":\t x = %f, y = %f \n", mouse2X, mouse2Y);
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
                            printf("Got a shape %d %d %d %d %d %f %f %f %f %f %f\n", drawshape, fillF % 2, colorR % 2, colorG % 2, colorB % 2, mouseX, mouseY, mouse2X, mouse2Y, mouse3X, mouse3Y);
                            break;
                        }
                        default:
                            break;
                    }
                    
                    
                    
                    
                    printf("Got a Mouse %s Event INSIDE CASE", action==GLFW_PRESS?"press":"release");
                    printf(":\t x = %f, y = %f \n", mouse2X, mouse2Y);
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

void cursor(GLFWwindow* window, double xpos, double ypos) {
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
            /*mouseX = 0;
            mouseY = 0;
            mouse2X = 0;
            mouse2Y = 0;*/
        }
    }
    ///printf("Got a Cursor Event");
    //printf(":\t x = %f, y = %f\n", xpos, ypos);
}

void keyboard(GLFWwindow *w, int key, int scancode, int action, int mods) {
    printf("Got a Keyboard Event: ");
    printf(" %d, ", key);
    
    switch(action) {
        case GLFW_PRESS :
            keyHold = 1;
            printf("pressed,\t");
            break;
        case GLFW_RELEASE :
            keyHold = 0;
            printf("released,\t");
            break;
        case GLFW_REPEAT :
            printf("repeated,\t");
            break;
        default :
            printf("shouldn't happen\t");
            break;
    }
    
    switch(mods) {
        case GLFW_MOD_SHIFT :
            printf("shift held\n");
            break;
        case GLFW_MOD_ALT :
            printf("alt held\n");
            break;
        case GLFW_MOD_CONTROL :
            printf("ctrl held\n");
            break;
        default :
            printf("no modifiers.\n");
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
            if(keyHold)
                fillF++;
            break;
        case 'r' :
        case 'R' :
            if(keyHold)
                colorR++;
            break;
        case 'g' :
        case 'G' :
            if(keyHold)
                colorG++;
            break;
        case 'b' :
        case 'B' :
            if(keyHold)
                colorB++;
            break;
        case 'c' :
        case 'C' :
            clear();
            break;
            
            
        case GLFW_KEY_F1 :
            drawshape =1;
            mouseX = 0;
            mouseY = 0;
            mouse2X = 0;
            mouse2Y = 0;
            mouse3X = 0;
            mouse3Y = 0;
            break;
        case GLFW_KEY_F2 :
            drawshape =2;
            mouseX = 0;
            mouseY = 0;
            mouse2X = 0;
            mouse2Y = 0;
            mouse3X = 0;
            mouse3Y = 0;
            break;
        case GLFW_KEY_F3 :
            drawshape =3;
            mouseX = 0;
            mouseY = 0;
            mouse2X = 0;
            mouse2Y = 0;
            mouse3X = 0;
            mouse3Y = 0;
            break;
        case GLFW_KEY_F4 :
            drawshape =4;
            mouseX = 0;
            mouseY = 0;
            mouse2X = 0;
            mouse2Y = 0;
            mouse3X = 0;
            mouse3Y = 0;
            break;
        default:
            break;
    }
}

void framebuffer_resize(GLFWwindow* w, int width, int height){
    glViewport(0, 0, width, height);
}

int main (int argc, char** argv){
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
