

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structs.h"

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
    
    f.normalize();
    up.normalize();
    
    s = crossProd(f, up);
    
    s.normalize();
    u = crossProd(s, f);
    
    return mat4(s.vec3arr[0], s.vec3arr[1], s.vec3arr[2], 0,
                u.vec3arr[0], u.vec3arr[1], u.vec3arr[2], 0,
                -f.vec3arr[0], -f.vec3arr[1], -f.vec3arr[2], 0,
                0,0,0,1);
}

mat4 anotherPerspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar){
    GLfloat f = 1/(tan(fovy*0.5*3.1415926/180));
    
    return mat4(f/aspect,   0,  0,                             0,
                0,          f,  0,                             0,
                0,          0,  (zFar + zNear)/(zNear -zFar),  -1,
                0,          0,  (2*zFar*zNear)/(zNear -zFar),  0);
    
    
}
#endif
