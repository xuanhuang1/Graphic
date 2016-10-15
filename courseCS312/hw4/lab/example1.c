// Two-Dimensional Sierpinski Gasket
// Generated using randomly selected vertices and bisection

//#include <stdio.h>
//#include <stdlib.h>
#include "common.h"
#include "functions.h"
//#include "structs.h"
//const int numPoints = 6;
GLuint vao, vbo1, vbo2, program, pos, col, ind;
//GLfloat colors[18];

mat4 transformM = mat4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
mat4 clipM = mat4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);

vec3 trans = vec3(0.2,0,0);
vec4 rotat = vec4(1,0,0, 90);

GLint MV, CV;


/*static const GLfloat  points[24][6] = {
    //0, 3, 2, 1
    {-0.5,-0.5,0.5, 1, 1, 1},{0.5,-0.5,0.5, 1, 1, 1},{0.5,0.5,0.5, 1, 1, 1},{-0.5,0.5,0.5, 1, 1, 1},
    //2, 3, 7, 6
    {0.5,0.5,0.5, 1, 1, 1},{0.5,-0.5,0.5, 1, 1, 1},{0.5,-0.5,-0.5, 1, 1, 1},{0.5,0.5,-0.5, 1, 1, 1},
    //0, 4, 7, 3
    {-0.5,-0.5,0.5, 1, 1, 1},{-0.5,-0.5,-0.5, 1, 1, 1},{0.5,-0.5,-0.5, 1, 1, 1},{0.5,-0.5,0.5, 1, 1, 1},
    //1, 2, 6, 5
    {-0.5,0.5,0.5, 1, 1, 1},{0.5,0.5,0.5, 1, 1, 1},{0.5,0.5,-0.5, 1, 1, 1},{-0.5,0.5,-0.5, 1, 1, 1},
    //4, 5, 6, 7
    {-0.5,-0.5,-0.5, 1, 1, 1},{-0.5,0.5,-0.5, 1, 1, 1},{0.5,0.5,-0.5, 1, 1, 1},{0.5,-0.5,-0.5, 1, 1, 1},
    //0, 1, 5, 4
    {-0.5,-0.5,0.5, 1, 1, 1},{-0.5,0.5,0.5, 1, 1, 1},{-0.5,0.5,-0.5, 1, 1, 1},{-0.5,-0.5,-0.5, 1, 1, 1}
};


static const GLuint elements[24] = {0,3,2,1,
    2,3,7,6,
    0,4,7,3,
    1,2,6,5,
    4,5,6,7,
    0,1,5,4};*/

GLuint indexBufferID;

// Specify the vertices for a triangle
static const GLfloat points[6][6] = {{0.0, 0.5, 0.0, 1.0, 0.0, 0.0}, {-0.5, -0.5, 0.0, 0.0, 1.0, 0.0}, {0.5, -0.5, 0.0, 0.0, 0.0, 1.0}, {0.0, 0.2, 0.5, 1.0, 1.0, 1.0}, {-0.5, 0.0, -0.5, 1.0, 1.0, 1.0}, {0.5, 0.0, -0.5, 1.0, 1.0, 1.0}};

static const GLuint elements[] = {
    0, 1, 2,
    3, 4, 5
};

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
    CV = glGetUniformLocation(program, "cameraview");
    
    //must have vbo bound
    
    //construct matrix here
    transformM = transformM.identity4();
    transformM = transformM.mul(anotherLookAt(vec3(1,1,1), vec3(0,0,0), vec3(0,1,0) ));
    transformM = transformM.mul(anotherTranslatef(vec3(0.2,0,0)));
    transformM = transformM.mul(anotherRotatef(rotat.vec4arr[3], vec3(rotat.vec4arr[0],rotat.vec4arr[1],rotat.vec4arr[2])));
    transformM = transformM.mul(anotherScalef(vec3(1,1,1)));
    
    clipM=clipM.identity4();
    //clipM = clipM.mul(anotherPerspective(30, 1, 0.1, 20));
    
    
    // Create and initialize a buffer object
    vbo1 = make_bo(GL_ARRAY_BUFFER, points, sizeof(points));
    vbo2 = make_bo(GL_ELEMENT_ARRAY_BUFFER, elements, sizeof(elements));
    
    
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*) 0);
    
    glEnableVertexAttribArray(col);
    glVertexAttribPointer(col, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    
    
    glUniformMatrix4fv(MV, 1, GL_FALSE, transformM.mat4arr);
    glUniformMatrix4fv(CV, 1, GL_FALSE, clipM.mat4arr);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
}

void draw(){
    
    drawTriangle(trans, rotat);
    
    rotat.vec4arr[3] += 1;
    //printf("%f ",rotat.vec4arr[3]);
}


void init( void ) {
    glEnable(GL_DEPTH_TEST);

    // Load shaders and use the resulting shader program
    program = initshader( "example1_vs.glsl", "example1_fs.glsl" );
    glUseProgram(program);

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
