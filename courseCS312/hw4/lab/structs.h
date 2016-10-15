

#ifndef STRUCTS_H
#define STRUCTS_H

#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

class vec2 {
public:
    GLfloat vec2arr[2];
    vec2 (GLfloat, GLfloat);
    void add (vec2);
    void normalize();
};

vec2::vec2 (GLfloat a, GLfloat b){
    vec2arr[0] = a;
    vec2arr[1] = b;
}

void vec2::normalize(){
    if (vec2arr[0] != 0 || vec2arr[1]!= 0) {
        GLfloat temp1 = vec2arr[0];
        GLfloat temp2 = vec2arr[1];
        vec2arr[0] = temp1/sqrt(pow(temp1,2)+pow(temp2,2));
        vec2arr[1] = temp2/sqrt(pow(temp1,2)+pow(temp2,2));
    }
}

void vec2::add(vec2 v2){
    vec2arr[0] += v2.vec2arr[0];
    vec2arr[1] += v2.vec2arr[1];
}



//      //
// vec3 //
//      //



class vec3 {
    public:
    GLfloat vec3arr[3];
    vec3 (GLfloat, GLfloat,GLfloat);
    void add (vec3);
    void normalize();
};

vec3::vec3 (GLfloat a, GLfloat b, GLfloat c){
    vec3arr[0] = a;
    vec3arr[1] = b;
    vec3arr[2] = c;
}

void vec3::normalize(){
    if (vec3arr[0] != 0 || vec3arr[1]!= 0 || vec3arr[2]!= 0) {
        GLfloat temp1 = vec3arr[0];
        GLfloat temp2 = vec3arr[1];
        GLfloat temp3 = vec3arr[2];
        vec3arr[0] = temp1/sqrt(pow(temp1,2)+pow(temp2,2)+pow(temp3,2));
        vec3arr[1] = temp2/sqrt(pow(temp1,2)+pow(temp2,2)+pow(temp3,2));
        vec3arr[2] = temp3/sqrt(pow(temp1,2)+pow(temp2,2)+pow(temp3,2));
    }
}

void vec3::add(vec3 v2){
    vec3arr[0] += v2.vec3arr[0];
    vec3arr[1] += v2.vec3arr[1];
    vec3arr[2] += v2.vec3arr[2];
}



//      //
// vec4 //
//      //





class vec4 {
    public:
    GLfloat vec4arr[12];
    vec4 (GLfloat, GLfloat,GLfloat, GLfloat);
    void add (vec4);
    void normalize();
};

vec4::vec4 (GLfloat a, GLfloat b, GLfloat c, GLfloat d){
    vec4arr[0] = a;
    vec4arr[1] = b;
    vec4arr[2] = c;
    vec4arr[3] = d;
}

void vec4::add(vec4 v2){
    vec4arr[0] += v2.vec4arr[0];
    vec4arr[1] += v2.vec4arr[1];
    vec4arr[2] += v2.vec4arr[2];
    vec4arr[3] += v2.vec4arr[3];
}

void vec4::normalize(){
    if (vec4arr[0] != 0 || vec4arr[1]!= 0 || vec4arr[2]!= 0 || vec4arr[3]!= 0) {
        GLfloat temp1 = vec4arr[0];
        GLfloat temp2 = vec4arr[1];
        GLfloat temp3 = vec4arr[2];
        GLfloat temp4 = vec4arr[3];
        vec4arr[0] = temp1/sqrt(pow(temp1,2)+pow(temp2,2)+pow(temp3,2)+pow(temp4,2));
        vec4arr[1] = temp2/sqrt(pow(temp1,2)+pow(temp2,2)+pow(temp3,2)+pow(temp4,2));
        vec4arr[2] = temp3/sqrt(pow(temp1,2)+pow(temp2,2)+pow(temp3,2)+pow(temp4,2));
        vec4arr[3] = temp4/sqrt(pow(temp1,2)+pow(temp2,2)+pow(temp3,2)+pow(temp4,2));
    }
}



//      //
// mat2 //
//      //




class mat2 {
    public:
    GLfloat mat2arr[4];
    mat2 (GLfloat, GLfloat,GLfloat, GLfloat);
    mat2 add (mat2);
    mat2 mul(mat2);
    mat2 identity2();
};

mat2::mat2 (GLfloat a, GLfloat b, GLfloat c, GLfloat d){
    mat2arr[0] = a;
    mat2arr[1] = b;
    mat2arr[2] = c;
    mat2arr[3] = d;
}

mat2 mat2::add (mat2 m2){
    GLfloat x0 = mat2arr[0] + m2.mat2arr[0];
    GLfloat x1 = mat2arr[1] + m2.mat2arr[1];
    GLfloat x2 = mat2arr[2] + m2.mat2arr[2];
    GLfloat x3 = mat2arr[3] + m2.mat2arr[3];
    return mat2(x0,x1,x2,x3);
}

mat2 mat2::identity2(){
    mat2 temp = mat2(1,0,
                     0,1);
    return temp;
}

mat2 mat2::mul(mat2 m2){
    GLfloat x0 = mat2arr[0] * m2.mat2arr[0] + mat2arr[1] * m2.mat2arr[2];
    GLfloat x1 = mat2arr[0] * m2.mat2arr[1] + mat2arr[1] * m2.mat2arr[3];
    GLfloat x2 = mat2arr[2] * m2.mat2arr[0] + mat2arr[3] * m2.mat2arr[2];
    GLfloat x3 = mat2arr[2] * m2.mat2arr[1] + mat2arr[3] * m2.mat2arr[3];
    return mat2(x0,x1,x2,x3);
}


//      //
// mat3 //
//      //



class mat3 {
    public:
    GLfloat mat3arr[9];
    mat3 (GLfloat,GLfloat,GLfloat,GLfloat, GLfloat,GLfloat,GLfloat,GLfloat, GLfloat);
    mat3 add(mat3);
    mat3 mul(mat3);
    mat3 identity3();
};

mat3::mat3 (GLfloat a, GLfloat b, GLfloat c, GLfloat d, GLfloat e, GLfloat f, GLfloat g, GLfloat h, GLfloat i){
    mat3arr[0] = a;
    mat3arr[1] = b;
    mat3arr[2] = c;
    mat3arr[3] = d;
    mat3arr[4] = e;
    mat3arr[5] = f;
    mat3arr[6] = g;
    mat3arr[7] = h;
    mat3arr[8] = i;
}

mat3 mat3::add (mat3 m2){
    GLfloat x0 = mat3arr[0] + m2.mat3arr[0];
    GLfloat x1 = mat3arr[1] + m2.mat3arr[1];
    GLfloat x2 = mat3arr[2] + m2.mat3arr[2];
    GLfloat x3 = mat3arr[3] + m2.mat3arr[3];
    GLfloat x4 = mat3arr[4] + m2.mat3arr[4];
    GLfloat x5 = mat3arr[5] + m2.mat3arr[5];
    GLfloat x6 = mat3arr[6] + m2.mat3arr[6];
    GLfloat x7 = mat3arr[7] + m2.mat3arr[7];
    GLfloat x8 = mat3arr[8] + m2.mat3arr[8];
    return mat3(x0,x1,x2,x3,x4,x5,x6,x7,x8);
}

mat3 mat3::mul(mat3 m2){
    GLfloat x0 = mat3arr[0] * m2.mat3arr[0] + mat3arr[1] * m2.mat3arr[3] + mat3arr[2] * m2.mat3arr[6];
    GLfloat x1 = mat3arr[0] * m2.mat3arr[1] + mat3arr[1] * m2.mat3arr[4] + mat3arr[2] * m2.mat3arr[7];
    GLfloat x2 = mat3arr[0] * m2.mat3arr[2] + mat3arr[1] * m2.mat3arr[5] + mat3arr[2] * m2.mat3arr[8];
    GLfloat x3 = mat3arr[3] * m2.mat3arr[0] + mat3arr[4] * m2.mat3arr[3] + mat3arr[5] * m2.mat3arr[6];
    GLfloat x4 = mat3arr[3] * m2.mat3arr[1] + mat3arr[4] * m2.mat3arr[4] + mat3arr[5] * m2.mat3arr[7];
    GLfloat x5 = mat3arr[3] * m2.mat3arr[2] + mat3arr[4] * m2.mat3arr[5] + mat3arr[5] * m2.mat3arr[8];
    GLfloat x6 = mat3arr[6] * m2.mat3arr[0] + mat3arr[7] * m2.mat3arr[3] + mat3arr[8] * m2.mat3arr[6];
    GLfloat x7 = mat3arr[6] * m2.mat3arr[1] + mat3arr[7] * m2.mat3arr[4] + mat3arr[8] * m2.mat3arr[7];
    GLfloat x8 = mat3arr[6] * m2.mat3arr[2] + mat3arr[7] * m2.mat3arr[5] + mat3arr[8] * m2.mat3arr[8];
    return mat3(x0,x1,x2,x3,x4,x5,x6,x7,x8);
}

mat3 mat3::identity3(){
    mat3 temp = mat3(1,0,0,
                     0,1,0,
                     0,0,1);
    return temp;
}


//      //
// mat4 //
//      //




class mat4 {
    public:
    GLfloat mat4arr[16];
    mat4 (GLfloat,GLfloat,GLfloat,GLfloat, GLfloat,GLfloat,GLfloat,GLfloat, GLfloat,GLfloat,GLfloat,GLfloat, GLfloat,GLfloat,GLfloat,GLfloat);
    mat4 add(mat4);
    mat4 mul(mat4);
    mat4 identity4();
    void transpose();
};

mat4::mat4 (GLfloat a, GLfloat b, GLfloat c, GLfloat d, GLfloat e, GLfloat f, GLfloat g, GLfloat h, GLfloat i, GLfloat j, GLfloat l, GLfloat m, GLfloat n, GLfloat o, GLfloat p, GLfloat q){
    mat4arr[0] = a;
    mat4arr[1] = b;
    mat4arr[2] = c;
    mat4arr[3] = d;
    mat4arr[4] = e;
    mat4arr[5] = f;
    mat4arr[6] = g;
    mat4arr[7] = h;
    mat4arr[8] = i;
    mat4arr[9] = j;
    mat4arr[10] = l;
    mat4arr[11] = m;
    mat4arr[12] = n;
    mat4arr[13] = o;
    mat4arr[14] = p;
    mat4arr[15] = q;
}

mat4 mat4::mul (mat4 m2){
    GLfloat x0 = mat4arr[0] * m2.mat4arr[0] + mat4arr[1] * m2.mat4arr[4] + mat4arr[2] * m2.mat4arr[8] + mat4arr[3] * m2.mat4arr[12];
    GLfloat x1 = mat4arr[0] * m2.mat4arr[1] + mat4arr[1] * m2.mat4arr[5] + mat4arr[2] * m2.mat4arr[9] + mat4arr[3] * m2.mat4arr[13];
    GLfloat x2 = mat4arr[0] * m2.mat4arr[2] + mat4arr[1] * m2.mat4arr[6] + mat4arr[2] * m2.mat4arr[10] + mat4arr[3] * m2.mat4arr[14];
    GLfloat x3 = mat4arr[0] * m2.mat4arr[3] + mat4arr[1] * m2.mat4arr[7] + mat4arr[2] * m2.mat4arr[11] + mat4arr[3] * m2.mat4arr[15];
    GLfloat x4 = mat4arr[4] * m2.mat4arr[0] + mat4arr[5] * m2.mat4arr[4] + mat4arr[6] * m2.mat4arr[8] + mat4arr[7] * m2.mat4arr[12];
    GLfloat x5 = mat4arr[4] * m2.mat4arr[1] + mat4arr[5] * m2.mat4arr[5] + mat4arr[6] * m2.mat4arr[9] + mat4arr[7] * m2.mat4arr[13];
    GLfloat x6 = mat4arr[4] * m2.mat4arr[2] + mat4arr[5] * m2.mat4arr[6] + mat4arr[6] * m2.mat4arr[10] + mat4arr[7] * m2.mat4arr[14];
    GLfloat x7 = mat4arr[4] * m2.mat4arr[3] + mat4arr[5] * m2.mat4arr[7] + mat4arr[6] * m2.mat4arr[11] + mat4arr[7] * m2.mat4arr[15];
    GLfloat x8 = mat4arr[8] * m2.mat4arr[0] + mat4arr[9] * m2.mat4arr[4] + mat4arr[10] * m2.mat4arr[8] + mat4arr[11] * m2.mat4arr[12];
    GLfloat x9 = mat4arr[8] * m2.mat4arr[1] + mat4arr[9] * m2.mat4arr[5] + mat4arr[10] * m2.mat4arr[9] + mat4arr[11] * m2.mat4arr[13];
    GLfloat x10 = mat4arr[8] * m2.mat4arr[2] + mat4arr[9] * m2.mat4arr[6] + mat4arr[10] * m2.mat4arr[10] + mat4arr[11] * m2.mat4arr[14];
    GLfloat x11 = mat4arr[8] * m2.mat4arr[3] + mat4arr[9] * m2.mat4arr[7] + mat4arr[10] * m2.mat4arr[11] + mat4arr[11] * m2.mat4arr[15];
    GLfloat x12 = mat4arr[12] * m2.mat4arr[0] + mat4arr[13] * m2.mat4arr[4] + mat4arr[14] * m2.mat4arr[8] + mat4arr[15] * m2.mat4arr[12];
    GLfloat x13 = mat4arr[12] * m2.mat4arr[1] + mat4arr[13] * m2.mat4arr[5] + mat4arr[14] * m2.mat4arr[9] + mat4arr[15] * m2.mat4arr[13];
    GLfloat x14 = mat4arr[12] * m2.mat4arr[2] + mat4arr[13] * m2.mat4arr[6] + mat4arr[14] * m2.mat4arr[10] + mat4arr[15] * m2.mat4arr[14];
    GLfloat x15 = mat4arr[12] * m2.mat4arr[3] + mat4arr[13] * m2.mat4arr[7] + mat4arr[14] * m2.mat4arr[11] + mat4arr[15] * m2.mat4arr[15];
    return mat4(x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15);
}

mat4 mat4::add (mat4 m2){
    GLfloat x0 = mat4arr[0] + m2.mat4arr[0];
    GLfloat x1 = mat4arr[1] + m2.mat4arr[1];
    GLfloat x2 = mat4arr[2] + m2.mat4arr[2];
    GLfloat x3 = mat4arr[3] + m2.mat4arr[3];
    GLfloat x4 = mat4arr[4] + m2.mat4arr[4];
    GLfloat x5 = mat4arr[5] + m2.mat4arr[5];
    GLfloat x6 = mat4arr[6] + m2.mat4arr[6];
    GLfloat x7 = mat4arr[7] + m2.mat4arr[7];
    GLfloat x8 = mat4arr[8] + m2.mat4arr[8];
    GLfloat x9 = mat4arr[9] + m2.mat4arr[9];
    GLfloat x10 = mat4arr[10] + m2.mat4arr[10];
    GLfloat x11 = mat4arr[11] + m2.mat4arr[11];
    GLfloat x12 = mat4arr[12] + m2.mat4arr[12];
    GLfloat x13 = mat4arr[13] + m2.mat4arr[13];
    GLfloat x14 = mat4arr[14] + m2.mat4arr[14];
    GLfloat x15 = mat4arr[15] + m2.mat4arr[15];
    return mat4(x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15);
}

mat4 mat4::identity4(){
        mat4 temp = mat4(1,0,0,0,
                         0,1,0,0,
                         0,0,1,0,
                         0,0,0,1);
        return temp;
    }

void mat4::transpose(){
    GLfloat tempArr[16] = {mat4arr[0], mat4arr[1],mat4arr[2],mat4arr[3],
                           mat4arr[4], mat4arr[5],mat4arr[6],mat4arr[7],
                           mat4arr[8], mat4arr[9],mat4arr[10],mat4arr[11],
                            mat4arr[12], mat4arr[13],mat4arr[14],mat4arr[15]};
    mat4arr[1] = tempArr[4];
    mat4arr[2] = tempArr[8];
    mat4arr[3] = tempArr[12];
    mat4arr[4] = tempArr[1];
    //mat4arr[5] = tempArr[5];
    mat4arr[6] = tempArr[9];
    mat4arr[7] = tempArr[13];
    mat4arr[8] = tempArr[2];
    mat4arr[9] = tempArr[6];
    //mat4arr[10] = tempArr[4];
    mat4arr[11] = tempArr[14];
    mat4arr[12] = tempArr[3];
    mat4arr[13] = tempArr[7];
    mat4arr[14] = tempArr[11];
    //mat4arr[15] = tempArr[4];
}

#endif


