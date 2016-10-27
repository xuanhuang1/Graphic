#ifndef __COMMON_H__
#define __COMMON_H__

//----------------------------------------------------------------------------
// 
// --- Include system headers ---
//

//  Define M_PI in the case it's not defined in the math header file
#ifndef M_PI
#  define M_PI  3.14159265358979323846
#endif

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

//  Helper function to load vertex and fragment shader files
GLuint initshader(const char* vertexShaderFile, const char* fragmentShaderFile);

#endif // __COMMON_H__
