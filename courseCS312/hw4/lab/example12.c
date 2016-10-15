// Two-Dimensional Sierpinski Gasket       
// Generated using randomly selected vertices and bisection

//#include <stdio.h>
//#include <stdlib.h>
#include "common.h"
#include "functions.h"
//#include "structs.h"
const int numPoints = 6;
GLuint vao, vbo1, vbo2, program, pos, col;
GLfloat points[numPoints*3];
GLfloat colors[numPoints*3];
mat4 transformM = mat4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);

vec3 trans = vec3(0.2,0,0);
vec4 rotat = vec4(0,0,1, 90);

GLint MV;


GLfloat vertices[][3] = {
    //0, 3, 2, 1
    {-1.0,-1.0,1.0},{1.0,-1.0,1.0},{1.0,1.0,1.0},{-1.0,1.0,1.0},
    //2, 3, 7, 6
    {1.0,1.0,1.0},{1.0,-1.0,1.0},{1.0,-1.0,-1.0},{1.0,1.0,-1.0},
    //0, 4, 7, 3
    {-1.0,-1.0,1.0},{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},{1.0,-1.0,1.0},
    //1, 2, 6, 5
    {-1.0,1.0,1.0},{1.0,1.0,1.0},{1.0,1.0,-1.0},{-1.0,1.0,-1.0},
    //4, 5, 6, 7
    {-1.0,-1.0,-1.0},{-1.0,1.0,-1.0},{1.0,1.0,-1.0},{1.0,-1.0,-1.0},
    //0, 1, 5, 4
    {-1.0,-1.0,1.0},{-1.0,1.0,1.0},{-1.0,1.0,-1.0},{-1.0,-1.0,-1.0}
};

// Specifiy the vertices for a triangle
//GLfloat vertices[3][2] = {{-0.5, -0.5}, {0.0, 0.5}, {0.5, -0.5}};

static GLuint make_bo(GLenum type, const void *buf, GLsizei buf_size) {
  GLuint bufnum;
  glGenBuffers(1, &bufnum);
  glBindBuffer(type, bufnum);
  glBufferData(type, buf_size, buf, GL_STATIC_DRAW);
  return bufnum;
}

void drawTriangle(vec3 transl, vec4 rotat){
    
    // Create a vertex array object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    // Initialize the vertex position attribute from the vertex shader
    pos = glGetAttribLocation(program, "vPos");
    col = glGetAttribLocation(program, "vCol");
    MV = glGetUniformLocation(program, "modelview");
    
    //must have vbo bound
    
    //construct matrix here
    transformM = transformM.identity4();
    //transformM = transformM.mul(anotherTranslatef(vec3(0.2,0,0)));
    transformM = transformM.mul(anotherRotatef(rotat.vec4arr[3], vec3(rotat.vec4arr[0],rotat.vec4arr[1],rotat.vec4arr[2])));
    
    
    // Create and initialize a buffer object
    vbo1 = make_bo(GL_ARRAY_BUFFER, points, sizeof(points));
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    
    vbo2 = make_bo(GL_ARRAY_BUFFER, colors, sizeof(colors));
    glEnableVertexAttribArray(col);
    glVertexAttribPointer(col, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    
    glUniformMatrix4fv(MV, 1, GL_FALSE, transformM.mat4arr);
    
    glDrawArrays(GL_TRIANGLES, 0, numPoints*3);
}



void draw(){
    
    drawTriangle(trans, rotat);
    
    rotat.vec4arr[3] += 1;
    printf("%f ",rotat.vec4arr[3]);
}


void init( void ) {
    glEnable(GL_DEPTH_TEST);

    // Load shaders and use the resulting shader program
    program = initshader( "example1_vs.glsl", "example1_fs.glsl" );
    glUseProgram(program);


    points[0] = -1.0;
    points[1] = -1.0;
    points[2] = 0;
    points[3] = 0.0;
    points[4] = 1;
    points[5] = 0;
    points[6] = 1.0;
    points[7] = -1.0;
    points[8] = 0;
    
    points[9] = -1;
    points[10] = 0.5;
    points[11] = -1;
    points[12] = 0;
    points[13] = 1;
    points[14] = 1;
    points[15] = 1;
    points[16] = 0.5;
    points[17] = -1;
    
    colors[0] = 1;
    colors[1] = 0;
    colors[2] = 0;
    colors[3] = 0;
    colors[4] = 1;
    colors[5] = 0;
    colors[6] = 0;
    colors[7] = 0;
    colors[8] = 1;
    colors[9] = 1;
    colors[10] = 0;
    colors[11] = 0;
    colors[12] = 0;
    colors[13] = 1;
    colors[14] = 0;
    colors[15] = 0;
    colors[16] = 0;
    colors[17] = 1;

    
    glClearColor( 0, 0, 0, 0 ); // white background
}

void keyboard(GLFWwindow *w, int key, int scancode, int action, int mods) {
    switch (key) {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(w, GL_TRUE);
            break;
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
    
    GLFWwindow *window = glfwCreateWindow (512, 512, "Hello Triangle", NULL, NULL);
    if (!window) {
        fprintf (stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent (window);
    
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
