#include "structs.h"


int main(){
    vec4 v = vec4(0,2,1,3);
    vec4 v2 = vec4(1,0,0,0);
    
    mat4 m = mat4(1,4,5,6,
                  8,2,1,5,
                  2,0,1,5,
                  7,3,0,9);
    mat4 m2 = mat4(3,0,12,2,
                   4,14,3,6,
                   10,4,8,4,
                   5,0,3,1);
    
    v.add(v2);
    v.normalize();
    printf("v1+v2: %f %f %f %f \n", v.vec4arr[0], v.vec4arr[1], v.vec4arr[2], v.vec4arr[3]);
    
    m=m.mul(m2);
    //m.identity4();
    printf("v1+v2: \n%f %f %f %f \n%f %f %f %f \n%f %f %f %f \n%f %f %f %f\n",
           m.mat4arr[0], m.mat4arr[1], m.mat4arr[2],
           m.mat4arr[3], m.mat4arr[4], m.mat4arr[5],
           m.mat4arr[6], m.mat4arr[7], m.mat4arr[8],
           m.mat4arr[9], m.mat4arr[10], m.mat4arr[11],
           m.mat4arr[12], m.mat4arr[13], m.mat4arr[14],  m.mat4arr[15]);
    m.transpose();
    printf("v1+v2: \n%f %f %f %f \n%f %f %f %f \n%f %f %f %f \n%f %f %f %f\n",
           m.mat4arr[0], m.mat4arr[1], m.mat4arr[2],
           m.mat4arr[3], m.mat4arr[4], m.mat4arr[5],
           m.mat4arr[6], m.mat4arr[7], m.mat4arr[8],
           m.mat4arr[9], m.mat4arr[10], m.mat4arr[11],
           m.mat4arr[12], m.mat4arr[13], m.mat4arr[14],  m.mat4arr[15]);
    
}